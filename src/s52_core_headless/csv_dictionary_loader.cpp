#include "marine_chart/s52_core_headless/csv_dictionary_loader.h"

#include <filesystem>
#include <fstream>

namespace marine_chart::s52_core_headless {
namespace {

[[nodiscard]] NeutralVector<NeutralString> parse_csv_line(NeutralStringView line) {
    NeutralVector<NeutralString> fields;
    NeutralString current_field;
    bool inside_quotes = false;

    for(std::size_t index = 0; index < line.size(); ++index) {
        const auto character = line[index];
        if(inside_quotes) {
            if(character == '"') {
                if(index + 1 < line.size() && line[index + 1] == '"') {
                    current_field.push_back('"');
                    ++index;
                } else {
                    inside_quotes = false;
                }
            } else {
                current_field.push_back(character);
            }
        } else if(character == '"') {
            inside_quotes = true;
        } else if(character == ',') {
            fields.push_back(current_field);
            current_field.clear();
        } else {
            current_field.push_back(character);
        }
    }

    fields.push_back(current_field);
    return fields;
}

}  // namespace

NeutralString csv_dictionary_path_from_asset_root(
    NeutralStringView asset_root,
    NeutralStringView file_name) {
    const auto path = std::filesystem::path{make_neutral_string(asset_root)} / make_neutral_string(file_name);
    return make_neutral_string(path.generic_string());
}

NeutralOptional<CsvDictionaryDocument> load_csv_dictionary_file(NeutralStringView csv_path) {
    std::ifstream input_stream{make_neutral_string(csv_path), std::ios::binary};
    if(!input_stream.is_open()) {
        return std::nullopt;
    }

    CsvDictionaryDocument document;
    document.source_path = make_neutral_string(csv_path);

    NeutralString line;
    bool header_loaded = false;
    while(std::getline(input_stream, line)) {
        if(!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if(line.empty()) {
            continue;
        }

        auto parsed_fields = parse_csv_line(line);
        if(!header_loaded) {
            document.header = std::move(parsed_fields);
            header_loaded = true;
            continue;
        }

        document.rows.push_back(CsvDictionaryRow{std::move(parsed_fields)});
    }

    if(!document.valid()) {
        return std::nullopt;
    }

    return document;
}

NeutralOptional<CsvDictionaryDocument> load_attribute_dictionary(NeutralStringView asset_root) {
    return load_csv_dictionary_file(csv_dictionary_path_from_asset_root(asset_root, "s57attributes.csv"));
}

NeutralOptional<CsvDictionaryDocument> load_object_class_dictionary(NeutralStringView asset_root) {
    return load_csv_dictionary_file(csv_dictionary_path_from_asset_root(asset_root, "s57objectclasses.csv"));
}

}  // namespace marine_chart::s52_core_headless
