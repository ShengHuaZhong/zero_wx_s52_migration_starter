#include "marine_chart/s52_core_headless/headless_core_init.h"

#include <string_view>

int main() {
    const auto explicit_initialization =
        marine_chart::s52_core_headless::initialize_headless_core("vendor/opencpn_s57data");
    if(!explicit_initialization.has_value() || !explicit_initialization->valid()) {
        return 1;
    }

    if(explicit_initialization->asset_root != "vendor/opencpn_s57data") {
        return 2;
    }

    if(explicit_initialization->chartsymbols_document.source_path.find("chartsymbols.xml")
        == std::string_view::npos) {
        return 3;
    }

    if(explicit_initialization->attribute_dictionary.header.empty()
        || explicit_initialization->attribute_dictionary.header.front() != "Code") {
        return 4;
    }

    if(explicit_initialization->object_class_dictionary.rows.empty()) {
        return 5;
    }

    const auto palette_match = explicit_initialization->asset_catalogs.palettes.palettes.find("DAY_BRIGHT");
    if(palette_match == explicit_initialization->asset_catalogs.palettes.palettes.end()) {
        return 6;
    }

    const auto symbol_match = explicit_initialization->asset_catalogs.symbols.symbols.find("ACHARE02");
    if(symbol_match == explicit_initialization->asset_catalogs.symbols.symbols.end()) {
        return 7;
    }

    const auto line_style_match =
        explicit_initialization->asset_catalogs.line_styles.line_styles.find("ACHARE51");
    if(line_style_match == explicit_initialization->asset_catalogs.line_styles.line_styles.end()) {
        return 8;
    }

    const auto pattern_match = explicit_initialization->asset_catalogs.patterns.patterns.find("AIRARE02");
    if(pattern_match == explicit_initialization->asset_catalogs.patterns.patterns.end()) {
        return 9;
    }

    const auto implicit_initialization = marine_chart::s52_core_headless::initialize_headless_core("");
    if(!implicit_initialization.has_value() || !implicit_initialization->valid()) {
        return 10;
    }

    if(implicit_initialization->asset_root.empty()) {
        return 11;
    }

    if(implicit_initialization->chartsymbols_document.source_path.find("chartsymbols.xml")
        == std::string_view::npos) {
        return 12;
    }

    return 0;
}
