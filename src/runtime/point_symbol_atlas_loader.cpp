#include "marine_chart/chart_runtime/point_symbol_atlas_loader.h"

namespace marine_chart::chart_runtime {

std::optional<PointSymbolAtlasEntry> load_point_symbol_atlas_entry(
    const s52_core_headless::AssetCatalogs& asset_catalogs,
    std::string_view palette_name,
    const PointSymbolIR& point_symbol_ir) {
    if(!point_symbol_ir.valid() || asset_catalogs.palettes.empty() || asset_catalogs.symbols.empty() || palette_name.empty()) {
        return std::nullopt;
    }

    const auto palette_match = asset_catalogs.palettes.palettes.find(std::string{palette_name});
    if(palette_match == asset_catalogs.palettes.palettes.end()) {
        return std::nullopt;
    }

    const auto symbol_match = asset_catalogs.symbols.symbols.find(point_symbol_ir.symbol_name);
    if(symbol_match == asset_catalogs.symbols.symbols.end()) {
        return std::nullopt;
    }

    PointSymbolAtlasEntry entry;
    entry.symbol_name = point_symbol_ir.symbol_name;
    entry.palette_name = std::string{palette_name};
    entry.graphics_file_name = palette_match->second.graphics_file_name;
    entry.source_x = symbol_match->second.source_rect.origin.x;
    entry.source_y = symbol_match->second.source_rect.origin.y;
    entry.source_width = symbol_match->second.source_rect.size.width;
    entry.source_height = symbol_match->second.source_rect.size.height;
    entry.pivot_x = symbol_match->second.pivot.x;
    entry.pivot_y = symbol_match->second.pivot.y;
    entry.color_token = symbol_match->second.color_reference;

    if(!entry.valid()) {
        return std::nullopt;
    }

    return entry;
}

}  // namespace marine_chart::chart_runtime
