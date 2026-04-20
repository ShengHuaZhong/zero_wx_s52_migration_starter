#include "marine_chart/s52_core_headless/asset_catalog_types.h"
#include "marine_chart/s52_core_headless/chartsymbols_xml_loader.h"
#include "marine_chart/s52_core_headless/color_table_loader.h"
#include "marine_chart/s52_core_headless/csv_dictionary_loader.h"
#include "marine_chart/s52_core_headless/line_style_loader.h"
#include "marine_chart/s52_core_headless/neutral_config_loader.h"
#include "marine_chart/s52_core_headless/neutral_font_descriptor.h"
#include "marine_chart/s52_core_headless/neutral_image_metadata.h"
#include "marine_chart/s52_core_headless/module.h"
#include "marine_chart/s52_core_headless/pattern_catalog_loader.h"
#include "marine_chart/s52_core_headless/symbol_catalog_loader.h"

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
    day_palette.graphics_file_name = "rastersymbols-day.png";
    day_palette.entries.emplace("CHBLK", marine_chart::s52_core_headless::make_neutral_color(18, 18, 18));
    asset_catalogs.palettes.palettes.emplace(day_palette.name, day_palette);

    marine_chart::s52_core_headless::SymbolDefinition symbol_definition;
    symbol_definition.rcid = "2035";
    symbol_definition.name = "BOYLAT";
    symbol_definition.description = "sample point symbol";
    symbol_definition.source_rect = marine_chart::s52_core_headless::make_neutral_rect(0, 0, 32, 32);
    symbol_definition.pivot = marine_chart::s52_core_headless::make_neutral_point(16, 16);
    symbol_definition.color_reference = "CHBLK";
    asset_catalogs.symbols.symbols.emplace(symbol_definition.name, symbol_definition);

    marine_chart::s52_core_headless::LineStyleDefinition line_style_definition;
    line_style_definition.rcid = "3346";
    line_style_definition.name = "DOTT";
    line_style_definition.description = "sample line style";
    line_style_definition.vector_size = marine_chart::s52_core_headless::make_neutral_size(16, 4);
    line_style_definition.pivot = marine_chart::s52_core_headless::make_neutral_point(8, 2);
    line_style_definition.origin = marine_chart::s52_core_headless::make_neutral_point(0, 0);
    line_style_definition.hpgl = "SP1,1,1";
    line_style_definition.color_reference = "CHBLK";
    asset_catalogs.line_styles.line_styles.emplace(line_style_definition.name, line_style_definition);

    marine_chart::s52_core_headless::PatternDefinition pattern_definition;
    pattern_definition.rcid = "2000";
    pattern_definition.name = "FOULAR01";
    pattern_definition.definition_code = "V";
    pattern_definition.fill_type = "S";
    pattern_definition.spacing = "C";
    pattern_definition.tile_size = marine_chart::s52_core_headless::make_neutral_size(64, 64);
    pattern_definition.pivot = marine_chart::s52_core_headless::make_neutral_point(32, 32);
    pattern_definition.origin = marine_chart::s52_core_headless::make_neutral_point(0, 0);
    pattern_definition.description = "sample pattern";
    pattern_definition.color_reference = "CHBLK";
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

    const auto color_tables =
        marine_chart::s52_core_headless::load_color_table_catalog_from_asset_root("vendor/opencpn_s57data");
    if(!color_tables.has_value() || color_tables->empty()) {
        return 48;
    }

    const auto day_bright = color_tables->palettes.find("DAY_BRIGHT");
    if(day_bright == color_tables->palettes.end()) {
        return 49;
    }

    if(day_bright->second.graphics_file_name != "rastersymbols-day.png") {
        return 50;
    }

    const auto chblk = day_bright->second.entries.find("CHBLK");
    if(chblk == day_bright->second.entries.end()) {
        return 51;
    }

    if(chblk->second != marine_chart::s52_core_headless::make_neutral_color(7, 7, 7)) {
        return 52;
    }

    const auto symbol_catalog =
        marine_chart::s52_core_headless::load_symbol_catalog_from_asset_root("vendor/opencpn_s57data");
    if(!symbol_catalog.has_value() || symbol_catalog->empty()) {
        return 53;
    }

    const auto achare02 = symbol_catalog->symbols.find("ACHARE02");
    if(achare02 == symbol_catalog->symbols.end()) {
        return 54;
    }

    if(achare02->second.rcid != "2035") {
        return 55;
    }

    if(achare02->second.source_rect != marine_chart::s52_core_headless::make_neutral_rect(10, 10, 13, 16)) {
        return 56;
    }

    if(achare02->second.pivot != marine_chart::s52_core_headless::make_neutral_point(6, 8)) {
        return 57;
    }

    if(achare02->second.color_reference != "ACHMGD") {
        return 58;
    }

    const auto line_style_catalog =
        marine_chart::s52_core_headless::load_line_style_catalog_from_asset_root("vendor/opencpn_s57data");
    if(!line_style_catalog.has_value() || line_style_catalog->empty()) {
        return 59;
    }

    const auto achare51 = line_style_catalog->line_styles.find("ACHARE51");
    if(achare51 == line_style_catalog->line_styles.end()) {
        return 60;
    }

    if(achare51->second.rcid != "3346") {
        return 61;
    }

    if(achare51->second.vector_size != marine_chart::s52_core_headless::make_neutral_size(3030, 503)) {
        return 62;
    }

    if(achare51->second.pivot != marine_chart::s52_core_headless::make_neutral_point(108, 820)) {
        return 63;
    }

    if(achare51->second.origin != marine_chart::s52_core_headless::make_neutral_point(306, 568)) {
        return 64;
    }

    if(achare51->second.color_reference != "ACHMGD") {
        return 65;
    }

    const auto pattern_catalog =
        marine_chart::s52_core_headless::load_pattern_catalog_from_asset_root("vendor/opencpn_s57data");
    if(!pattern_catalog.has_value() || pattern_catalog->empty()) {
        return 66;
    }

    const auto airare02 = pattern_catalog->patterns.find("AIRARE02");
    if(airare02 == pattern_catalog->patterns.end()) {
        return 67;
    }

    if(airare02->second.rcid != "2000") {
        return 68;
    }

    if(airare02->second.definition_code != "V") {
        return 69;
    }

    if(airare02->second.fill_type != "S" || airare02->second.spacing != "C") {
        return 70;
    }

    if(airare02->second.tile_size != marine_chart::s52_core_headless::make_neutral_size(618, 528)) {
        return 71;
    }

    if(airare02->second.pivot != marine_chart::s52_core_headless::make_neutral_point(2259, 2256)) {
        return 72;
    }

    if(airare02->second.origin != marine_chart::s52_core_headless::make_neutral_point(435, 452)) {
        return 73;
    }

    if(airare02->second.color_reference != "ALANDF") {
        return 74;
    }

    return 0;
}
