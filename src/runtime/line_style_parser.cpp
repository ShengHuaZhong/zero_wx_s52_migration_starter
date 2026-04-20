#include "marine_chart/chart_runtime/line_style_parser.h"

#include <charconv>
#include <string_view>

namespace marine_chart::chart_runtime {
namespace {

[[nodiscard]] std::optional<std::string_view> parse_field(
    std::string_view text,
    std::size_t& start_offset) noexcept {
    if(start_offset >= text.size()) {
        return std::nullopt;
    }

    const auto field_end = text.find_first_of(",)", start_offset);
    if(field_end == std::string_view::npos) {
        return std::nullopt;
    }

    const auto field = text.substr(start_offset, field_end - start_offset);
    start_offset = field_end + 1;
    return field;
}

}  // namespace

std::optional<ParsedLineStyle> parse_line_style(const LineStyleIR& line_style_ir) noexcept {
    if(!line_style_ir.valid()) {
        return std::nullopt;
    }

    const std::string_view instruction = line_style_ir.instruction.source.raw_instruction;
    const auto ls_begin = instruction.find("LS(");
    if(ls_begin == std::string_view::npos) {
        return std::nullopt;
    }

    std::size_t parse_offset = ls_begin + 3;
    const auto style_name = parse_field(instruction, parse_offset);
    const auto width_text = parse_field(instruction, parse_offset);
    const auto color_token = parse_field(instruction, parse_offset);
    if(!style_name.has_value() || !width_text.has_value() || !color_token.has_value() || style_name->empty()
        || color_token->empty()) {
        return std::nullopt;
    }

    int width = 0;
    const auto width_parse = std::from_chars(width_text->data(), width_text->data() + width_text->size(), width);
    if(width_parse.ec != std::errc{} || width <= 0) {
        return std::nullopt;
    }

    ParsedLineStyle parsed_line_style;
    parsed_line_style.style_name = std::string{*style_name};
    parsed_line_style.width = width;
    parsed_line_style.color_token = std::string{*color_token};

    if(!parsed_line_style.valid()) {
        return std::nullopt;
    }

    return parsed_line_style;
}

}  // namespace marine_chart::chart_runtime
