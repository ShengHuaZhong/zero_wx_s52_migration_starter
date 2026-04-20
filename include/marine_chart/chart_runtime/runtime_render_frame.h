#pragma once

#include "marine_chart/chart_runtime/area_renderer.h"
#include "marine_chart/chart_runtime/line_renderer.h"
#include "marine_chart/chart_runtime/point_renderer.h"
#include "marine_chart/chart_runtime/priority_sorter.h"
#include "marine_chart/chart_runtime/text_renderer.h"
#include "marine_chart/s52_core_headless/asset_catalog_types.h"

#include <cstddef>
#include <vector>

namespace marine_chart::chart_runtime {

struct RuntimeRenderFrame final {
    std::vector<PointRenderCommand> point_commands;
    std::vector<LineRenderCommand> line_commands;
    std::vector<AreaRenderCommand> area_commands;
    std::vector<TextRenderCommand> text_commands;
    std::vector<PrioritySortedInstruction> sorted_instructions;

    [[nodiscard]] bool empty() const noexcept {
        return point_commands.empty() && line_commands.empty() && area_commands.empty() && text_commands.empty()
            && sorted_instructions.empty();
    }

    [[nodiscard]] std::size_t command_count() const noexcept {
        return point_commands.size() + line_commands.size() + area_commands.size() + text_commands.size();
    }

    bool operator==(const RuntimeRenderFrame&) const noexcept = default;
};

[[nodiscard]] RuntimeRenderFrame build_runtime_render_frame(
    const RuntimePortrayalBuffer& buffer,
    const s52_core_headless::AssetCatalogs& asset_catalogs,
    const RuntimePaletteColors& palette_colors);

}  // namespace marine_chart::chart_runtime
