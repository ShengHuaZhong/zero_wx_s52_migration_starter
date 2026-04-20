#include "marine_chart/chart_runtime/area_renderer.h"

namespace marine_chart::chart_runtime {

std::optional<AreaRenderCommand> build_area_render_command(
    const AreaPatternIR& area_pattern_ir,
    const std::optional<PatternAtlasEntry>& pattern_atlas_entry,
    const RuntimePaletteColors& palette_colors) noexcept {
    if(!area_pattern_ir.valid() || palette_colors.empty()) {
        return std::nullopt;
    }

    AreaRenderCommand command;
    command.instruction_id = area_pattern_ir.instruction.stable_id;
    command.boundary_line_style_name = area_pattern_ir.boundary_line_style_name;

    if(!area_pattern_ir.fill_color_token.empty()) {
        const auto fill_color = find_runtime_palette_color(palette_colors, area_pattern_ir.fill_color_token);
        if(fill_color.has_value()) {
            command.fill_color = *fill_color;
        }
    }

    if(!area_pattern_ir.pattern_name.empty()) {
        if(!pattern_atlas_entry.has_value() || !pattern_atlas_entry->valid()
            || pattern_atlas_entry->pattern_name != area_pattern_ir.pattern_name
            || pattern_atlas_entry->palette_name != palette_colors.palette_name) {
            return std::nullopt;
        }

        command.pattern_name = pattern_atlas_entry->pattern_name;
        command.graphics_file_name = pattern_atlas_entry->graphics_file_name;
        command.definition_code = pattern_atlas_entry->definition_code;
        command.fill_type = pattern_atlas_entry->fill_type;
        command.spacing = pattern_atlas_entry->spacing;
        command.tile_width = pattern_atlas_entry->tile_width;
        command.tile_height = pattern_atlas_entry->tile_height;
        command.pivot_x = pattern_atlas_entry->pivot_x;
        command.pivot_y = pattern_atlas_entry->pivot_y;
        command.origin_x = pattern_atlas_entry->origin_x;
        command.origin_y = pattern_atlas_entry->origin_y;
        command.pattern_color = find_runtime_palette_color(palette_colors, pattern_atlas_entry->color_token)
                                    .value_or(make_runtime_color(255, 255, 255));
    }

    if(!command.valid()) {
        return std::nullopt;
    }

    return command;
}

}  // namespace marine_chart::chart_runtime
