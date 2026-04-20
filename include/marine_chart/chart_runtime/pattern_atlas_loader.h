#pragma once

#include "marine_chart/chart_runtime/area_pattern_ir.h"
#include "marine_chart/s52_core_headless/asset_catalog_types.h"

#include <optional>
#include <string>
#include <string_view>

namespace marine_chart::chart_runtime {

struct PatternAtlasEntry final {
    std::string pattern_name;
    std::string palette_name;
    std::string graphics_file_name;
    std::string definition_code;
    std::string fill_type;
    std::string spacing;
    int tile_width{0};
    int tile_height{0};
    int pivot_x{0};
    int pivot_y{0};
    int origin_x{0};
    int origin_y{0};
    std::string color_token;
    std::string pattern_source;

    [[nodiscard]] bool valid() const noexcept {
        return !pattern_name.empty() && !palette_name.empty() && !graphics_file_name.empty() && !definition_code.empty()
            && !fill_type.empty() && !spacing.empty() && tile_width > 0 && tile_height > 0 && !color_token.empty()
            && !pattern_source.empty();
    }

    bool operator==(const PatternAtlasEntry&) const noexcept = default;
};

[[nodiscard]] std::optional<PatternAtlasEntry> load_pattern_atlas_entry(
    const s52_core_headless::AssetCatalogs& asset_catalogs,
    std::string_view palette_name,
    const AreaPatternIR& area_pattern_ir);

}  // namespace marine_chart::chart_runtime
