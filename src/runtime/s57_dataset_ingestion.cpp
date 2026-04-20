#include "marine_chart/chart_runtime/s57_dataset_ingestion.h"

#include "marine_chart/s52_core_headless/csv_dictionary_loader.h"

#include <algorithm>
#include <charconv>
#include <cctype>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace marine_chart::chart_runtime {
namespace {

struct DirectoryEntry final {
    std::string tag;
    std::size_t field_length{0};
    std::size_t field_offset{0};
};

[[nodiscard]] bool parse_decimal(
    const std::uint8_t* text,
    std::size_t text_length,
    std::size_t& value) noexcept {
    if(text == nullptr || text_length == 0) {
        return false;
    }

    value = 0;
    for(std::size_t index = 0; index < text_length; ++index) {
        if(!std::isdigit(static_cast<unsigned char>(text[index]))) {
            return false;
        }

        value = value * 10 + static_cast<std::size_t>(text[index] - static_cast<std::uint8_t>('0'));
    }

    return true;
}

[[nodiscard]] std::optional<DirectoryEntry> parse_directory_entry(
    const std::vector<std::uint8_t>& file_bytes,
    std::size_t entry_offset,
    std::size_t field_tag_size,
    std::size_t field_length_size,
    std::size_t field_position_size) {
    if(entry_offset >= file_bytes.size() || field_tag_size == 0 || field_length_size == 0 || field_position_size == 0) {
        return std::nullopt;
    }

    const auto entry_size = field_tag_size + field_length_size + field_position_size;
    if(entry_offset + entry_size > file_bytes.size()) {
        return std::nullopt;
    }

    DirectoryEntry entry;
    entry.tag = std::string{
        reinterpret_cast<const char*>(file_bytes.data() + entry_offset),
        field_tag_size};

    if(!parse_decimal(
           file_bytes.data() + entry_offset + field_tag_size,
           field_length_size,
           entry.field_length)) {
        return std::nullopt;
    }

    if(!parse_decimal(
           file_bytes.data() + entry_offset + field_tag_size + field_length_size,
           field_position_size,
           entry.field_offset)) {
        return std::nullopt;
    }

    return entry;
}

[[nodiscard]] s52_core_headless::FeaturePrimitiveType map_primitive_code(std::uint8_t primitive_code) noexcept {
    switch(primitive_code) {
    case 1:
        return s52_core_headless::FeaturePrimitiveType::point;
    case 2:
        return s52_core_headless::FeaturePrimitiveType::line;
    case 3:
        return s52_core_headless::FeaturePrimitiveType::area;
    default:
        return s52_core_headless::FeaturePrimitiveType::unknown;
    }
}

[[nodiscard]] std::optional<int> parse_object_class_code(
    const s52_core_headless::NeutralString& field_text) noexcept {
    int code = 0;
    const auto parse_result =
        std::from_chars(field_text.data(), field_text.data() + field_text.size(), code);
    if(parse_result.ec != std::errc{} || parse_result.ptr != field_text.data() + field_text.size() || code <= 0) {
        return std::nullopt;
    }

    return code;
}

[[nodiscard]] bool has_numeric_s57_cell_extension(const std::filesystem::path& file_path) {
    const auto extension = file_path.extension().string();
    if(extension.size() != 4 || extension[0] != '.') {
        return false;
    }

    return std::isdigit(static_cast<unsigned char>(extension[1]))
        && std::isdigit(static_cast<unsigned char>(extension[2]))
        && std::isdigit(static_cast<unsigned char>(extension[3]));
}

[[nodiscard]] bool decode_frid_field(
    const std::uint8_t* field_data,
    std::size_t field_length,
    int& object_class_code,
    s52_core_headless::FeaturePrimitiveType& primitive_type) noexcept {
    if(field_data == nullptr || field_length < 12) {
        return false;
    }

    std::size_t data_length = field_length;
    if(field_data[data_length - 1] == 0x1E) {
        --data_length;
    }

    if(data_length < 12) {
        return false;
    }

    primitive_type = map_primitive_code(field_data[5]);
    if(primitive_type == s52_core_headless::FeaturePrimitiveType::unknown) {
        return false;
    }

    object_class_code = static_cast<int>(field_data[7]) | (static_cast<int>(field_data[8]) << 8);
    return object_class_code > 0;
}

[[nodiscard]] std::optional<std::vector<std::uint8_t>> read_binary_file(
    const std::filesystem::path& file_path) {
    std::ifstream input(file_path, std::ios::binary);
    if(!input.is_open()) {
        return std::nullopt;
    }

    return std::vector<std::uint8_t>(
        std::istreambuf_iterator<char>(input),
        std::istreambuf_iterator<char>{});
}

void ingest_s57_cell_file(
    const std::filesystem::path& file_path,
    const std::unordered_map<int, std::string>& object_class_by_code,
    std::unordered_set<std::string>& seen_feature_keys,
    S57DatasetLoadResult& result) {
    const auto file_bytes = read_binary_file(file_path);
    if(!file_bytes.has_value() || file_bytes->empty()) {
        return;
    }

    std::size_t record_offset = 0;
    while(record_offset + 24 <= file_bytes->size()) {
        std::size_t record_length = 0;
        if(!parse_decimal(file_bytes->data() + record_offset, 5, record_length)) {
            return;
        }

        if(record_length < 24 || record_offset + record_length > file_bytes->size()) {
            return;
        }

        std::size_t base_address = 0;
        std::size_t field_length_size = 0;
        std::size_t field_position_size = 0;
        std::size_t field_tag_size = 0;
        if(!parse_decimal(file_bytes->data() + record_offset + 12, 5, base_address)
            || !parse_decimal(file_bytes->data() + record_offset + 20, 1, field_length_size)
            || !parse_decimal(file_bytes->data() + record_offset + 21, 1, field_position_size)
            || !parse_decimal(file_bytes->data() + record_offset + 23, 1, field_tag_size)) {
            return;
        }

        const auto entry_size = field_tag_size + field_length_size + field_position_size;
        if(entry_size == 0 || base_address <= 24 || base_address > record_length) {
            return;
        }

        const auto directory_start = record_offset + 24;
        const auto directory_end = record_offset + base_address - 1;
        std::size_t entry_offset = directory_start;
        while(entry_offset + entry_size <= directory_end) {
            if((*file_bytes)[entry_offset] == 0x1E) {
                break;
            }

            const auto entry =
                parse_directory_entry(*file_bytes, entry_offset, field_tag_size, field_length_size, field_position_size);
            if(!entry.has_value()) {
                return;
            }

            entry_offset += entry_size;
            if(entry->tag != "FRID") {
                continue;
            }

            const auto field_data_offset = record_offset + base_address + entry->field_offset;
            if(field_data_offset + entry->field_length > record_offset + record_length) {
                return;
            }

            int object_class_code = 0;
            s52_core_headless::FeaturePrimitiveType primitive_type = s52_core_headless::FeaturePrimitiveType::unknown;
            if(!decode_frid_field(
                   file_bytes->data() + field_data_offset,
                   entry->field_length,
                   object_class_code,
                   primitive_type)) {
                continue;
            }

            ++result.frid_record_count;

            const auto class_match = object_class_by_code.find(object_class_code);
            if(class_match == object_class_by_code.end()) {
                continue;
            }

            const auto feature_key =
                class_match->second + "#" + std::to_string(static_cast<unsigned int>(primitive_type));
            if(!seen_feature_keys.insert(feature_key).second) {
                continue;
            }

            s52_core_headless::RuleLayerFeature feature;
            feature.object_class = class_match->second;
            feature.primitive_type = primitive_type;
            result.features.push_back(std::move(feature));
        }

        record_offset += record_length;
    }

    ++result.source_file_count;
}

}  // namespace

std::optional<S57DatasetLoadResult> load_rule_layer_features_from_s57_dataset(
    std::string_view dataset_root,
    std::string_view asset_root) {
    if(dataset_root.empty() || asset_root.empty()) {
        return std::nullopt;
    }

    const std::filesystem::path dataset_path{dataset_root};
    if(!std::filesystem::exists(dataset_path) || !std::filesystem::is_directory(dataset_path)) {
        return std::nullopt;
    }

    const auto object_dictionary = s52_core_headless::load_object_class_dictionary(asset_root);
    if(!object_dictionary.has_value() || !object_dictionary->valid()) {
        return std::nullopt;
    }

    std::unordered_map<int, std::string> object_class_by_code;
    object_class_by_code.reserve(object_dictionary->rows.size());
    for(const auto& row : object_dictionary->rows) {
        if(row.fields.size() < 3 || row.fields[2].empty()) {
            continue;
        }

        const auto code = parse_object_class_code(row.fields[0]);
        if(!code.has_value()) {
            continue;
        }

        object_class_by_code.emplace(*code, row.fields[2]);
    }

    if(object_class_by_code.empty()) {
        return std::nullopt;
    }

    S57DatasetLoadResult result;
    std::unordered_set<std::string> seen_feature_keys;

    std::vector<std::filesystem::path> dataset_files;
    for(const auto& entry : std::filesystem::directory_iterator(dataset_path)) {
        if(!entry.is_regular_file() || !has_numeric_s57_cell_extension(entry.path())) {
            continue;
        }

        dataset_files.push_back(entry.path());
    }

    std::sort(dataset_files.begin(), dataset_files.end());
    for(const auto& dataset_file : dataset_files) {
        ingest_s57_cell_file(dataset_file, object_class_by_code, seen_feature_keys, result);
    }

    return result;
}

}  // namespace marine_chart::chart_runtime
