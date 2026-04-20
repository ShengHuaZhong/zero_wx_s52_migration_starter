#pragma once

#include "marine_chart/chart_runtime/pattern_atlas_loader.h"
#include "marine_chart/chart_runtime/runtime_palette_colors.h"

#include <optional>
#include <string>

namespace marine_chart::chart_runtime {

struct AreaRenderCommand final {
    std::string instruction_id;
    std::optional<RuntimeColor> fill_color;
    std::string pattern_name;
    std::string graphics_file_name;
    std::string definition_code;
    std::string fill_type;
    std::string spacing;
    int tile_width{0};
    int tile_height{0};
    int pivot_x{0};
    int pivot_y{0};
    int origin_x{0};
    int origin_y{0};
    std::optional<RuntimeColor> pattern_color;
    std::string boundary_line_style_name;

    [[nodiscard]] bool has_fill() const noexcept {
        return fill_color.has_value();
    }

    [[nodiscard]] bool has_pattern() const noexcept {
        return !pattern_name.empty() && !graphics_file_name.empty() && !definition_code.empty() && !fill_type.empty()
            && !spacing.empty() && tile_width > 0 && tile_height > 0 && pattern_color.has_value();
    }

    [[nodiscard]] bool valid() const noexcept {
        return !instruction_id.empty() && (has_fill() || has_pattern());
    }

    bool operator==(const AreaRenderCommand&) const noexcept = default;
};

[[nodiscard]] std::optional<AreaRenderCommand> build_area_render_command(
    const AreaPatternIR& area_pattern_ir,
    const std::optional<PatternAtlasEntry>& pattern_atlas_entry,
    const RuntimePaletteColors& palette_colors) noexcept;

}  // namespace marine_chart::chart_runtime
