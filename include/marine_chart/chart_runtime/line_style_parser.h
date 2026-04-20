#pragma once

#include "marine_chart/chart_runtime/line_style_ir.h"

#include <optional>
#include <string>

namespace marine_chart::chart_runtime {

struct ParsedLineStyle final {
    std::string style_name;
    int width{0};
    std::string color_token;

    [[nodiscard]] bool valid() const noexcept {
        return !style_name.empty() && width > 0 && !color_token.empty();
    }

    bool operator==(const ParsedLineStyle&) const noexcept = default;
};

[[nodiscard]] std::optional<ParsedLineStyle> parse_line_style(const LineStyleIR& line_style_ir) noexcept;

}  // namespace marine_chart::chart_runtime
