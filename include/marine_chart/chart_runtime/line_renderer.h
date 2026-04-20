#pragma once

#include "marine_chart/chart_runtime/line_style_parser.h"
#include "marine_chart/chart_runtime/runtime_palette_colors.h"

#include <optional>
#include <string>

namespace marine_chart::chart_runtime {

struct LineRenderCommand final {
    std::string instruction_id;
    std::string style_name;
    int width{0};
    RuntimeColor stroke_color{};

    [[nodiscard]] bool valid() const noexcept {
        return !instruction_id.empty() && !style_name.empty() && width > 0;
    }

    bool operator==(const LineRenderCommand&) const noexcept = default;
};

[[nodiscard]] std::optional<LineRenderCommand> build_line_render_command(
    const LineStyleIR& line_style_ir,
    const ParsedLineStyle& parsed_line_style,
    const RuntimePaletteColors& palette_colors) noexcept;

}  // namespace marine_chart::chart_runtime
