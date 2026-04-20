#pragma once

#include "marine_chart/chart_runtime/text_rule_ir.h"

#include <optional>
#include <string>

namespace marine_chart::chart_runtime {

struct TextLayout final {
    TextRuleKind rule_kind{TextRuleKind::unknown};
    std::string format_string;
    std::string attribute_name;
    int horizontal_justification_code{-1};
    int vertical_justification_code{-1};
    int spacing_code{-1};
    std::string font_reference;
    int x_offset{0};
    int y_offset{0};
    std::string color_token;
    int display_parameter{-1};

    [[nodiscard]] bool valid() const noexcept {
        return rule_kind != TextRuleKind::unknown && !attribute_name.empty()
            && horizontal_justification_code >= 0 && vertical_justification_code >= 0 && spacing_code >= 0
            && !font_reference.empty() && !color_token.empty() && display_parameter >= 0;
    }

    bool operator==(const TextLayout&) const noexcept = default;
};

[[nodiscard]] std::optional<TextLayout> parse_text_layout(const TextRuleIR& text_rule_ir) noexcept;

}  // namespace marine_chart::chart_runtime
