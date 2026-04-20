#include "marine_chart/chart_runtime/runtime_render_frame.h"

#include <set>
#include <string>

namespace marine_chart::chart_runtime {
namespace {

template <typename Command>
void append_command(
    std::vector<Command>& commands,
    std::set<std::string, std::less<>>& available_instruction_ids,
    const std::optional<Command>& command) {
    if(!command.has_value()) {
        return;
    }

    available_instruction_ids.insert(command->instruction_id);
    commands.push_back(*command);
}

}  // namespace

RuntimeRenderFrame build_runtime_render_frame(
    const RuntimePortrayalBuffer& buffer,
    const s52_core_headless::AssetCatalogs& asset_catalogs,
    const RuntimePaletteColors& palette_colors) {
    RuntimeRenderFrame frame;
    if(palette_colors.empty()) {
        return frame;
    }

    std::set<std::string, std::less<>> available_instruction_ids;

    for(const auto& point_symbol_ir : buffer.point_symbols) {
        const auto atlas_entry = load_point_symbol_atlas_entry(asset_catalogs, palette_colors.palette_name, point_symbol_ir);
        append_command(
            frame.point_commands,
            available_instruction_ids,
            atlas_entry.has_value() ? build_point_render_command(point_symbol_ir, *atlas_entry, palette_colors)
                                    : std::nullopt);
    }

    for(const auto& line_style_ir : buffer.line_styles) {
        const auto parsed_line_style = parse_line_style(line_style_ir);
        append_command(
            frame.line_commands,
            available_instruction_ids,
            parsed_line_style.has_value() ? build_line_render_command(line_style_ir, *parsed_line_style, palette_colors)
                                          : std::nullopt);
    }

    for(const auto& area_pattern_ir : buffer.area_patterns) {
        std::optional<PatternAtlasEntry> pattern_atlas_entry;
        if(!area_pattern_ir.pattern_name.empty()) {
            pattern_atlas_entry = load_pattern_atlas_entry(asset_catalogs, palette_colors.palette_name, area_pattern_ir);
        }

        append_command(
            frame.area_commands,
            available_instruction_ids,
            build_area_render_command(area_pattern_ir, pattern_atlas_entry, palette_colors));
    }

    for(const auto& text_rule_ir : buffer.text_rules) {
        const auto text_layout = parse_text_layout(text_rule_ir);
        append_command(
            frame.text_commands,
            available_instruction_ids,
            text_layout.has_value() ? build_text_render_command(text_rule_ir, *text_layout, palette_colors)
                                    : std::nullopt);
    }

    for(const auto& sorted_instruction : sort_render_instructions_by_priority(buffer)) {
        if(available_instruction_ids.contains(sorted_instruction.instruction_id)) {
            frame.sorted_instructions.push_back(sorted_instruction);
        }
    }

    return frame;
}

}  // namespace marine_chart::chart_runtime
