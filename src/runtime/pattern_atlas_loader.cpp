#include "marine_chart/chart_runtime/pattern_atlas_loader.h"

namespace marine_chart::chart_runtime {

std::optional<PatternAtlasEntry> load_pattern_atlas_entry(
    const s52_core_headless::AssetCatalogs& asset_catalogs,
    std::string_view palette_name,
    const AreaPatternIR& area_pattern_ir) {
    if(!area_pattern_ir.valid() || area_pattern_ir.pattern_name.empty() || asset_catalogs.palettes.empty()
        || asset_catalogs.patterns.empty() || palette_name.empty()) {
        return std::nullopt;
    }

    const auto palette_match = asset_catalogs.palettes.palettes.find(std::string{palette_name});
    if(palette_match == asset_catalogs.palettes.palettes.end()) {
        return std::nullopt;
    }

    const auto pattern_match = asset_catalogs.patterns.patterns.find(area_pattern_ir.pattern_name);
    if(pattern_match == asset_catalogs.patterns.patterns.end()) {
        return std::nullopt;
    }

    PatternAtlasEntry entry;
    entry.pattern_name = area_pattern_ir.pattern_name;
    entry.palette_name = std::string{palette_name};
    entry.graphics_file_name = palette_match->second.graphics_file_name;
    entry.definition_code = pattern_match->second.definition_code;
    entry.fill_type = pattern_match->second.fill_type;
    entry.spacing = pattern_match->second.spacing;
    entry.tile_width = pattern_match->second.tile_size.width;
    entry.tile_height = pattern_match->second.tile_size.height;
    entry.pivot_x = pattern_match->second.pivot.x;
    entry.pivot_y = pattern_match->second.pivot.y;
    entry.origin_x = pattern_match->second.origin.x;
    entry.origin_y = pattern_match->second.origin.y;
    entry.color_token = pattern_match->second.color_reference;
    entry.pattern_source = pattern_match->second.pattern_source;

    if(!entry.valid()) {
        return std::nullopt;
    }

    return entry;
}

}  // namespace marine_chart::chart_runtime
