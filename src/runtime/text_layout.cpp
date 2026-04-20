#include "marine_chart/chart_runtime/text_layout.h"

#include <charconv>
#include <cctype>
#include <string_view>
#include <vector>

namespace marine_chart::chart_runtime {
namespace {

[[nodiscard]] std::string_view trim(std::string_view value) noexcept {
    while(!value.empty() && std::isspace(static_cast<unsigned char>(value.front())) != 0) {
        value.remove_prefix(1);
    }

    while(!value.empty() && std::isspace(static_cast<unsigned char>(value.back())) != 0) {
        value.remove_suffix(1);
    }

    return value;
}

[[nodiscard]] std::string unquote(std::string_view value) {
    value = trim(value);
    if(value.size() >= 2 && value.front() == '\'' && value.back() == '\'') {
        value.remove_prefix(1);
        value.remove_suffix(1);
    }

    return std::string{value};
}

[[nodiscard]] std::optional<int> parse_int(std::string_view value) noexcept {
    value = trim(value);
    if(value.empty()) {
        return std::nullopt;
    }

    int parsed_value = 0;
    const auto [ptr, ec] = std::from_chars(value.data(), value.data() + value.size(), parsed_value);
    if(ec != std::errc{} || ptr != value.data() + value.size()) {
        return std::nullopt;
    }

    return parsed_value;
}

[[nodiscard]] std::optional<std::vector<std::string_view>> split_arguments(std::string_view arguments) {
    std::vector<std::string_view> result;
    std::size_t token_start = 0;
    bool in_quote = false;

    for(std::size_t index = 0; index < arguments.size(); ++index) {
        const char current = arguments[index];
        if(current == '\'') {
            in_quote = !in_quote;
            continue;
        }

        if(current == ',' && !in_quote) {
            result.push_back(trim(arguments.substr(token_start, index - token_start)));
            token_start = index + 1;
        }
    }

    if(in_quote) {
        return std::nullopt;
    }

    result.push_back(trim(arguments.substr(token_start)));
    return result;
}

[[nodiscard]] std::optional<TextLayout> parse_tx_layout(std::string_view arguments) noexcept {
    const auto parts = split_arguments(arguments);
    if(!parts.has_value() || parts->size() != 9) {
        return std::nullopt;
    }

    const auto horizontal = parse_int((*parts)[1]);
    const auto vertical = parse_int((*parts)[2]);
    const auto spacing = parse_int((*parts)[3]);
    const auto x_offset = parse_int((*parts)[5]);
    const auto y_offset = parse_int((*parts)[6]);
    const auto display_parameter = parse_int((*parts)[8]);
    if(!horizontal.has_value() || !vertical.has_value() || !spacing.has_value() || !x_offset.has_value()
        || !y_offset.has_value() || !display_parameter.has_value()) {
        return std::nullopt;
    }

    TextLayout layout;
    layout.rule_kind = TextRuleKind::tx;
    layout.attribute_name = unquote((*parts)[0]);
    layout.horizontal_justification_code = *horizontal;
    layout.vertical_justification_code = *vertical;
    layout.spacing_code = *spacing;
    layout.font_reference = unquote((*parts)[4]);
    layout.x_offset = *x_offset;
    layout.y_offset = *y_offset;
    layout.color_token = unquote((*parts)[7]);
    layout.display_parameter = *display_parameter;
    return layout.valid() ? std::optional<TextLayout>{layout} : std::nullopt;
}

[[nodiscard]] std::optional<TextLayout> parse_te_layout(std::string_view arguments) noexcept {
    const auto parts = split_arguments(arguments);
    if(!parts.has_value() || parts->size() != 10) {
        return std::nullopt;
    }

    const auto horizontal = parse_int((*parts)[2]);
    const auto vertical = parse_int((*parts)[3]);
    const auto spacing = parse_int((*parts)[4]);
    const auto x_offset = parse_int((*parts)[6]);
    const auto y_offset = parse_int((*parts)[7]);
    const auto display_parameter = parse_int((*parts)[9]);
    if(!horizontal.has_value() || !vertical.has_value() || !spacing.has_value() || !x_offset.has_value()
        || !y_offset.has_value() || !display_parameter.has_value()) {
        return std::nullopt;
    }

    TextLayout layout;
    layout.rule_kind = TextRuleKind::te;
    layout.format_string = unquote((*parts)[0]);
    layout.attribute_name = unquote((*parts)[1]);
    layout.horizontal_justification_code = *horizontal;
    layout.vertical_justification_code = *vertical;
    layout.spacing_code = *spacing;
    layout.font_reference = unquote((*parts)[5]);
    layout.x_offset = *x_offset;
    layout.y_offset = *y_offset;
    layout.color_token = unquote((*parts)[8]);
    layout.display_parameter = *display_parameter;
    return layout.valid() ? std::optional<TextLayout>{layout} : std::nullopt;
}

}  // namespace

std::optional<TextLayout> parse_text_layout(const TextRuleIR& text_rule_ir) noexcept {
    if(!text_rule_ir.valid()) {
        return std::nullopt;
    }

    const auto instruction_text = std::string_view{text_rule_ir.instruction_text};
    const auto open_paren = instruction_text.find('(');
    const auto close_paren = instruction_text.rfind(')');
    if(open_paren == std::string::npos || close_paren == std::string::npos || close_paren <= open_paren) {
        return std::nullopt;
    }

    const auto function_name = trim(instruction_text.substr(0, open_paren));
    const auto arguments = instruction_text.substr(open_paren + 1, close_paren - open_paren - 1);

    if(text_rule_ir.rule_kind == TextRuleKind::tx && function_name == "TX") {
        return parse_tx_layout(arguments);
    }

    if(text_rule_ir.rule_kind == TextRuleKind::te && function_name == "TE") {
        return parse_te_layout(arguments);
    }

    return std::nullopt;
}

}  // namespace marine_chart::chart_runtime
