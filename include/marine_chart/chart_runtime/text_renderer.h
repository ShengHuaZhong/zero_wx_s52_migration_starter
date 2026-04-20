#pragma once

#include "marine_chart/chart_runtime/runtime_palette_colors.h"
#include "marine_chart/chart_runtime/text_layout.h"

#include <optional>
#include <string>

namespace marine_chart::chart_runtime {

struct TextRenderCommand final {
    std::string instruction_id;
    TextRuleKind rule_kind{TextRuleKind::unknown};
    std::string format_string;
    std::string attribute_name;
    int horizontal_justification_code{-1};
    int vertical_justification_code{-1};
    int spacing_code{-1};
    std::string font_reference;
    int x_offset{0};
    int y_offset{0};
    RuntimeColor text_color{};
    int display_parameter{-1};

    [[nodiscard]] bool valid() const noexcept {
        return !instruction_id.empty() && rule_kind != TextRuleKind::unknown && !attribute_name.empty()
            && horizontal_justification_code >= 0 && vertical_justification_code >= 0 && spacing_code >= 0
            && !font_reference.empty() && display_parameter >= 0;
    }

    bool operator==(const TextRenderCommand&) const noexcept = default;
};

[[nodiscard]] std::optional<TextRenderCommand> build_text_render_command(
    const TextRuleIR& text_rule_ir,
    const TextLayout& text_layout,
    const RuntimePaletteColors& palette_colors) noexcept;

}  // namespace marine_chart::chart_runtime
