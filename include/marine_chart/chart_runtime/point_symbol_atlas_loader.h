#pragma once

#include "marine_chart/chart_runtime/point_symbol_ir.h"
#include "marine_chart/s52_core_headless/asset_catalog_types.h"

#include <optional>
#include <string>
#include <string_view>

namespace marine_chart::chart_runtime {

struct PointSymbolAtlasEntry final {
    std::string symbol_name;
    std::string palette_name;
    std::string graphics_file_name;
    int source_x{0};
    int source_y{0};
    int source_width{0};
    int source_height{0};
    int pivot_x{0};
    int pivot_y{0};
    std::string color_token;

    [[nodiscard]] bool valid() const noexcept {
        return !symbol_name.empty() && !palette_name.empty() && !graphics_file_name.empty() && source_width > 0
            && source_height > 0 && !color_token.empty();
    }

    bool operator==(const PointSymbolAtlasEntry&) const noexcept = default;
};

[[nodiscard]] std::optional<PointSymbolAtlasEntry> load_point_symbol_atlas_entry(
    const s52_core_headless::AssetCatalogs& asset_catalogs,
    std::string_view palette_name,
    const PointSymbolIR& point_symbol_ir);

}  // namespace marine_chart::chart_runtime
