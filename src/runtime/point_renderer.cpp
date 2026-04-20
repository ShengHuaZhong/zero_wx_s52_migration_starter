#include "marine_chart/chart_runtime/point_renderer.h"

namespace marine_chart::chart_runtime {

std::optional<PointRenderCommand> build_point_render_command(
    const PointSymbolIR& point_symbol_ir,
    const PointSymbolAtlasEntry& atlas_entry,
    const RuntimePaletteColors& palette_colors) noexcept {
    if(!point_symbol_ir.valid() || !atlas_entry.valid() || atlas_entry.symbol_name != point_symbol_ir.symbol_name
        || palette_colors.palette_name != atlas_entry.palette_name) {
        return std::nullopt;
    }

    PointRenderCommand command;
    command.instruction_id = point_symbol_ir.instruction.stable_id;
    command.symbol_name = point_symbol_ir.symbol_name;
    command.graphics_file_name = atlas_entry.graphics_file_name;
    command.source_x = atlas_entry.source_x;
    command.source_y = atlas_entry.source_y;
    command.source_width = atlas_entry.source_width;
    command.source_height = atlas_entry.source_height;
    command.pivot_x = atlas_entry.pivot_x;
    command.pivot_y = atlas_entry.pivot_y;
    command.tint_color =
        find_runtime_palette_color(palette_colors, atlas_entry.color_token).value_or(make_runtime_color(255, 255, 255));

    if(!command.valid()) {
        return std::nullopt;
    }

    return command;
}

}  // namespace marine_chart::chart_runtime
