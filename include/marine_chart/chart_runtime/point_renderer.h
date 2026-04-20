#pragma once

#include "marine_chart/chart_runtime/point_symbol_atlas_loader.h"
#include "marine_chart/chart_runtime/runtime_palette_colors.h"

#include <optional>
#include <string>

namespace marine_chart::chart_runtime {

struct PointRenderCommand final {
    std::string instruction_id;
    std::string symbol_name;
    std::string graphics_file_name;
    int source_x{0};
    int source_y{0};
    int source_width{0};
    int source_height{0};
    int pivot_x{0};
    int pivot_y{0};
    RuntimeColor tint_color{};

    [[nodiscard]] bool valid() const noexcept {
        return !instruction_id.empty() && !symbol_name.empty() && !graphics_file_name.empty() && source_width > 0
            && source_height > 0;
    }

    bool operator==(const PointRenderCommand&) const noexcept = default;
};

[[nodiscard]] std::optional<PointRenderCommand> build_point_render_command(
    const PointSymbolIR& point_symbol_ir,
    const PointSymbolAtlasEntry& atlas_entry,
    const RuntimePaletteColors& palette_colors) noexcept;

}  // namespace marine_chart::chart_runtime
