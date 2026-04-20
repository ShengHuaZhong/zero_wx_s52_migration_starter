#pragma once

#include "marine_chart/s52_core_headless/asset_catalog_types.h"
#include "marine_chart/s52_core_headless/chartsymbols_xml_loader.h"
#include "marine_chart/s52_core_headless/csv_dictionary_loader.h"
#include "marine_chart/s52_core_headless/neutral_containers.h"
#include "marine_chart/s52_core_headless/neutral_string.h"

namespace marine_chart::s52_core_headless {

struct HeadlessCoreInitialization final {
    NeutralString asset_root;
    ChartsymbolsXmlDocument chartsymbols_document;
    CsvDictionaryDocument attribute_dictionary;
    CsvDictionaryDocument object_class_dictionary;
    AssetCatalogs asset_catalogs;

    [[nodiscard]] bool valid() const noexcept {
        return !asset_root.empty()
            && chartsymbols_document.valid()
            && attribute_dictionary.valid()
            && object_class_dictionary.valid()
            && !asset_catalogs.palettes.empty()
            && !asset_catalogs.symbols.empty()
            && !asset_catalogs.line_styles.empty()
            && !asset_catalogs.patterns.empty();
    }
};

[[nodiscard]] NeutralOptional<HeadlessCoreInitialization> initialize_headless_core(
    NeutralStringView requested_asset_root);

}  // namespace marine_chart::s52_core_headless
