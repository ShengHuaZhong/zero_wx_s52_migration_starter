#include "marine_chart/s52_core_headless/asset_catalog_types.h"
#include "marine_chart/s52_core_headless/chartsymbols_xml_loader.h"
#include "marine_chart/s52_core_headless/csv_dictionary_loader.h"
#include "marine_chart/s52_core_headless/neutral_config_loader.h"
#include "marine_chart/s52_core_headless/neutral_font_descriptor.h"
#include "marine_chart/s52_core_headless/neutral_image_metadata.h"
#include "marine_chart/s52_core_headless/module.h"

#include <string_view>

int main() {
    const auto neutral_string = marine_chart::s52_core_headless::make_neutral_string("core");
    if(neutral_string != "core") {
        return 1;
    }

    if(marine_chart::s52_core_headless::as_string_view(neutral_string) != "core") {
        return 2;
    }

    const auto module_info = marine_chart::s52_core_headless::describe_module();

    if(module_info.name != "s52_core_headless") {
        return 3;
    }

    if(module_info.responsibility.find("Zero-wx") == std::string_view::npos) {
        return 4;
    }

    const auto expected_color = marine_chart::s52_core_headless::make_neutral_color(24, 64, 128);
    if(module_info.accent_color != expected_color) {
        return 5;
    }

    if(!module_info.accent_color.is_opaque()) {
        return 6;
    }

    const auto expected_viewport = marine_chart::s52_core_headless::make_neutral_rect(10, 20, 640, 480);
    if(module_info.default_viewport != expected_viewport) {
        return 7;
    }

    if(!module_info.default_viewport.contains(
        marine_chart::s52_core_headless::make_neutral_point(100, 100))) {
        return 8;
    }

    if(module_info.default_viewport.contains(
        marine_chart::s52_core_headless::make_neutral_point(0, 0))) {
        return 9;
    }

    if(module_info.default_viewport.is_empty()) {
        return 10;
    }

    if(module_info.capability_tags.size() != 2) {
        return 11;
    }

    if(module_info.capability_tags.front() != "headless") {
        return 12;
    }

    const auto render_path = module_info.defaults.find("render-path");
    if(render_path == module_info.defaults.end()) {
        return 13;
    }

    if(render_path->second != "rhi") {
        return 14;
    }

    const auto config = marine_chart::s52_core_headless::load_neutral_config_from_text(
        "# module defaults\n"
        "render-path = rhi\n"
        "role = portrayal-core\n");
    const auto config_render_path = marine_chart::s52_core_headless::find_config_value(config, "render-path");
    if(!config_render_path.has_value()) {
        return 15;
    }

    if(*config_render_path != "rhi") {
        return 16;
    }

    const auto missing_value = marine_chart::s52_core_headless::find_config_value(config, "missing");
    if(missing_value.has_value()) {
        return 17;
    }

    const auto image_metadata = marine_chart::s52_core_headless::make_neutral_image_metadata(
        "symbol-atlas",
        "vendor/opencpn_s57data/rastersymbols-day.png",
        512,
        512);
    if(image_metadata.resource_name != "symbol-atlas") {
        return 18;
    }

    if(image_metadata.pixel_size != marine_chart::s52_core_headless::make_neutral_size(512, 512)) {
        return 19;
    }

    if(image_metadata.pixel_format != marine_chart::s52_core_headless::ImagePixelFormat::rgba8) {
        return 20;
    }

    if(!image_metadata.has_alpha) {
        return 21;
    }

    if(image_metadata.is_empty()) {
        return 22;
    }

    const auto font_descriptor = marine_chart::s52_core_headless::make_neutral_font_descriptor(
        "Noto Sans",
        12,
        marine_chart::s52_core_headless::FontWeight::bold,
        marine_chart::s52_core_headless::FontSlant::italic,
        true);
    if(font_descriptor.family_name != "Noto Sans") {
        return 23;
    }

    if(font_descriptor.point_size != 12) {
        return 24;
    }

    if(font_descriptor.weight != marine_chart::s52_core_headless::FontWeight::bold) {
        return 25;
    }

    if(font_descriptor.slant != marine_chart::s52_core_headless::FontSlant::italic) {
        return 26;
    }

    if(!font_descriptor.underline) {
        return 27;
    }

    if(!font_descriptor.is_valid()) {
        return 28;
    }

    marine_chart::s52_core_headless::AssetCatalogs asset_catalogs;

    marine_chart::s52_core_headless::PaletteDefinition day_palette;
    day_palette.name = "DAY";
    day_palette.entries.emplace("CHBLK", marine_chart::s52_core_headless::make_neutral_color(18, 18, 18));
    asset_catalogs.palettes.palettes.emplace(day_palette.name, day_palette);

    marine_chart::s52_core_headless::SymbolDefinition symbol_definition;
    symbol_definition.name = "BOYLAT";
    symbol_definition.atlas = marine_chart::s52_core_headless::make_neutral_image_metadata(
        "symbol-atlas",
        "vendor/opencpn_s57data/rastersymbols-day.png",
        512,
        512);
    symbol_definition.source_rect = marine_chart::s52_core_headless::make_neutral_rect(0, 0, 32, 32);
    symbol_definition.pivot = marine_chart::s52_core_headless::make_neutral_point(16, 16);
    asset_catalogs.symbols.symbols.emplace(symbol_definition.name, symbol_definition);

    marine_chart::s52_core_headless::LineStyleDefinition line_style_definition;
    line_style_definition.name = "DOTT";
    line_style_definition.vector_source = "SP1,1,1";
    asset_catalogs.line_styles.line_styles.emplace(line_style_definition.name, line_style_definition);

    marine_chart::s52_core_headless::PatternDefinition pattern_definition;
    pattern_definition.name = "FOULAR01";
    pattern_definition.tile_size = marine_chart::s52_core_headless::make_neutral_size(64, 64);
    pattern_definition.pattern_source = "PATTERN-SOURCE";
    asset_catalogs.patterns.patterns.emplace(pattern_definition.name, pattern_definition);

    if(asset_catalogs.empty()) {
        return 29;
    }

    if(asset_catalogs.palettes.empty()) {
        return 30;
    }

    const auto palette_match = asset_catalogs.palettes.palettes.find("DAY");
    if(palette_match == asset_catalogs.palettes.palettes.end()) {
        return 31;
    }

    if(palette_match->second.entries.find("CHBLK") == palette_match->second.entries.end()) {
        return 32;
    }

    const auto symbol_match = asset_catalogs.symbols.symbols.find("BOYLAT");
    if(symbol_match == asset_catalogs.symbols.symbols.end() || symbol_match->second.empty()) {
        return 33;
    }

    const auto line_match = asset_catalogs.line_styles.line_styles.find("DOTT");
    if(line_match == asset_catalogs.line_styles.line_styles.end() || line_match->second.empty()) {
        return 34;
    }

    const auto pattern_match = asset_catalogs.patterns.patterns.find("FOULAR01");
    if(pattern_match == asset_catalogs.patterns.patterns.end() || pattern_match->second.empty()) {
        return 35;
    }

    const auto chartsymbols_document =
        marine_chart::s52_core_headless::load_chartsymbols_xml("vendor/opencpn_s57data");
    if(!chartsymbols_document.has_value()) {
        return 36;
    }

    if(!chartsymbols_document->valid()) {
        return 37;
    }

    if(chartsymbols_document->source_path.find("chartsymbols.xml") == std::string_view::npos) {
        return 38;
    }

    if(chartsymbols_document->xml_text.find("<chartsymbols>") == std::string_view::npos) {
        return 39;
    }

    if(!chartsymbols_document->has_color_tables
        || !chartsymbols_document->has_line_styles
        || !chartsymbols_document->has_patterns
        || !chartsymbols_document->has_symbols) {
        return 40;
    }

    const auto attribute_dictionary =
        marine_chart::s52_core_headless::load_attribute_dictionary("vendor/opencpn_s57data");
    if(!attribute_dictionary.has_value() || !attribute_dictionary->valid()) {
        return 41;
    }

    if(attribute_dictionary->header.size() < 5 || attribute_dictionary->header.front() != "Code") {
        return 42;
    }

    if(attribute_dictionary->rows.empty() || attribute_dictionary->rows.front().fields.size() < 3) {
        return 43;
    }

    if(attribute_dictionary->rows.front().fields[2] != "AGENCY") {
        return 44;
    }

    const auto object_class_dictionary =
        marine_chart::s52_core_headless::load_object_class_dictionary("vendor/opencpn_s57data");
    if(!object_class_dictionary.has_value() || !object_class_dictionary->valid()) {
        return 45;
    }

    bool found_beacon_cardinal = false;
    for(const auto& row : object_class_dictionary->rows) {
        if(row.fields.size() >= 3 && row.fields[2] == "BCNCAR") {
            if(row.fields[1] != "Beacon, cardinal") {
                return 46;
            }

            found_beacon_cardinal = true;
            break;
        }
    }

    if(!found_beacon_cardinal) {
        return 47;
    }

    return 0;
}
