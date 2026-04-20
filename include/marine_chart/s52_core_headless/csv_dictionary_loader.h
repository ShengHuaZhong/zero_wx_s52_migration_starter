#pragma once

#include "marine_chart/s52_core_headless/neutral_containers.h"
#include "marine_chart/s52_core_headless/neutral_string.h"

namespace marine_chart::s52_core_headless {

struct CsvDictionaryRow final {
    NeutralVector<NeutralString> fields;

    [[nodiscard]] bool empty() const noexcept {
        return fields.empty();
    }
};

struct CsvDictionaryDocument final {
    NeutralString source_path;
    NeutralVector<NeutralString> header;
    NeutralVector<CsvDictionaryRow> rows;

    [[nodiscard]] bool valid() const noexcept {
        return !source_path.empty() && !header.empty() && !rows.empty();
    }
};

[[nodiscard]] NeutralString csv_dictionary_path_from_asset_root(
    NeutralStringView asset_root,
    NeutralStringView file_name);

[[nodiscard]] NeutralOptional<CsvDictionaryDocument> load_csv_dictionary_file(
    NeutralStringView csv_path);

[[nodiscard]] NeutralOptional<CsvDictionaryDocument> load_attribute_dictionary(
    NeutralStringView asset_root);

[[nodiscard]] NeutralOptional<CsvDictionaryDocument> load_object_class_dictionary(
    NeutralStringView asset_root);

}  // namespace marine_chart::s52_core_headless
