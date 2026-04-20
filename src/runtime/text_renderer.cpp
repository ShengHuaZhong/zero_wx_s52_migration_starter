#include "marine_chart/chart_runtime/text_renderer.h"

namespace marine_chart::chart_runtime {

std::optional<TextRenderCommand> build_text_render_command(
    const TextRuleIR& text_rule_ir,
    const TextLayout& text_layout,
    const RuntimePaletteColors& palette_colors) noexcept {
    if(!text_rule_ir.valid() || !text_layout.valid() || palette_colors.empty()) {
        return std::nullopt;
    }

    const auto parsed_layout = parse_text_layout(text_rule_ir);
    if(!parsed_layout.has_value() || *parsed_layout != text_layout) {
        return std::nullopt;
    }

    const auto text_color = find_runtime_palette_color(palette_colors, text_layout.color_token);
    if(!text_color.has_value()) {
        return std::nullopt;
    }

    TextRenderCommand command;
    command.instruction_id = text_rule_ir.instruction.stable_id;
    command.rule_kind = text_layout.rule_kind;
    command.format_string = text_layout.format_string;
    command.attribute_name = text_layout.attribute_name;
    command.horizontal_justification_code = text_layout.horizontal_justification_code;
    command.vertical_justification_code = text_layout.vertical_justification_code;
    command.spacing_code = text_layout.spacing_code;
    command.font_reference = text_layout.font_reference;
    command.x_offset = text_layout.x_offset;
    command.y_offset = text_layout.y_offset;
    command.text_color = *text_color;
    command.display_parameter = text_layout.display_parameter;

    if(!command.valid()) {
        return std::nullopt;
    }

    return command;
}

}  // namespace marine_chart::chart_runtime
