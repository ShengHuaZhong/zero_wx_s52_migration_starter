#include "marine_chart/chart_runtime/line_renderer.h"

namespace marine_chart::chart_runtime {

std::optional<LineRenderCommand> build_line_render_command(
    const LineStyleIR& line_style_ir,
    const ParsedLineStyle& parsed_line_style,
    const RuntimePaletteColors& palette_colors) noexcept {
    if(!line_style_ir.valid() || !parsed_line_style.valid() || palette_colors.empty()
        || parsed_line_style.style_name != line_style_ir.line_style_name) {
        return std::nullopt;
    }

    const auto stroke_color = find_runtime_palette_color(palette_colors, parsed_line_style.color_token);
    if(!stroke_color.has_value()) {
        return std::nullopt;
    }

    LineRenderCommand command;
    command.instruction_id = line_style_ir.instruction.stable_id;
    command.style_name = parsed_line_style.style_name;
    command.width = parsed_line_style.width;
    command.stroke_color = *stroke_color;

    if(!command.valid()) {
        return std::nullopt;
    }

    return command;
}

}  // namespace marine_chart::chart_runtime
