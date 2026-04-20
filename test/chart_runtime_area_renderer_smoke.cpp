#include "marine_chart/chart_runtime/area_renderer.h"
#include "marine_chart/s52_core_headless/headless_core_init.h"

int main() {
    const auto initialization = marine_chart::s52_core_headless::initialize_headless_core("vendor/opencpn_s57data");
    if(!initialization.has_value() || !initialization->valid()) {
        return 1;
    }

    marine_chart::chart_runtime::AreaPatternIR area_pattern_ir;
    area_pattern_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::area_pattern;
    area_pattern_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::area;
    area_pattern_ir.instruction.stable_id = "area-pattern:AIRARE:77";
    area_pattern_ir.instruction.source.object_class = "AIRARE";
    area_pattern_ir.instruction.source.lookup_type = "Area";
    area_pattern_ir.instruction.source.table_name = "Plain";
    area_pattern_ir.instruction.source.lookup_id = "77";
    area_pattern_ir.fill_color_token = "AREAFILL";
    area_pattern_ir.pattern_name = "AIRARE02";
    area_pattern_ir.boundary_line_style_name = "SOLD";

    const auto pattern_atlas_entry =
        marine_chart::chart_runtime::load_pattern_atlas_entry(initialization->asset_catalogs, "DAY_BRIGHT", area_pattern_ir);
    if(!pattern_atlas_entry.has_value()) {
        return 2;
    }

    marine_chart::chart_runtime::RuntimePaletteColors palette_colors;
    palette_colors.palette_name = "DAY_BRIGHT";
    palette_colors.graphics_file_name = "rastersymbols-day.png";
    palette_colors.entries.emplace("AREAFILL", marine_chart::chart_runtime::make_runtime_color(210, 220, 230));
    palette_colors.entries.emplace(
        pattern_atlas_entry->color_token,
        marine_chart::chart_runtime::make_runtime_color(44, 88, 132));

    const auto render_command =
        marine_chart::chart_runtime::build_area_render_command(area_pattern_ir, pattern_atlas_entry, palette_colors);
    if(!render_command.has_value() || render_command->instruction_id != "area-pattern:AIRARE:77"
        || !render_command->fill_color.has_value()
        || *render_command->fill_color != marine_chart::chart_runtime::make_runtime_color(210, 220, 230)
        || !render_command->pattern_color.has_value()
        || *render_command->pattern_color != marine_chart::chart_runtime::make_runtime_color(44, 88, 132)
        || render_command->pattern_name != "AIRARE02"
        || render_command->graphics_file_name != "rastersymbols-day.png"
        || render_command->tile_width <= 0
        || render_command->tile_height <= 0
        || render_command->boundary_line_style_name != "SOLD") {
        return 3;
    }

    marine_chart::chart_runtime::AreaPatternIR solid_fill_ir = area_pattern_ir;
    solid_fill_ir.pattern_name.clear();
    solid_fill_ir.boundary_line_style_name.clear();

    const auto solid_fill_command =
        marine_chart::chart_runtime::build_area_render_command(solid_fill_ir, std::nullopt, palette_colors);
    if(!solid_fill_command.has_value() || !solid_fill_command->has_fill() || solid_fill_command->has_pattern()) {
        return 4;
    }

    marine_chart::chart_runtime::RuntimePaletteColors missing_fill_palette = palette_colors;
    missing_fill_palette.entries.erase("AREAFILL");
    const auto pattern_only_command =
        marine_chart::chart_runtime::build_area_render_command(area_pattern_ir, pattern_atlas_entry, missing_fill_palette);
    if(!pattern_only_command.has_value() || pattern_only_command->has_fill() || !pattern_only_command->has_pattern()) {
        return 5;
    }

    marine_chart::chart_runtime::RuntimePaletteColors missing_pattern_palette = palette_colors;
    missing_pattern_palette.entries.erase(pattern_atlas_entry->color_token);
    const auto fallback_pattern_command = marine_chart::chart_runtime::build_area_render_command(
        area_pattern_ir,
        pattern_atlas_entry,
        missing_pattern_palette);
    if(!fallback_pattern_command.has_value()
        || !fallback_pattern_command->pattern_color.has_value()
        || *fallback_pattern_command->pattern_color
            != marine_chart::chart_runtime::make_runtime_color(255, 255, 255)) {
        return 6;
    }

    auto wrong_pattern_entry = pattern_atlas_entry;
    wrong_pattern_entry->pattern_name = "OTHER01";
    if(marine_chart::chart_runtime::build_area_render_command(area_pattern_ir, wrong_pattern_entry, palette_colors)
           .has_value()) {
        return 7;
    }

    marine_chart::chart_runtime::AreaPatternIR boundary_only_ir = area_pattern_ir;
    boundary_only_ir.fill_color_token.clear();
    boundary_only_ir.pattern_name.clear();
    if(marine_chart::chart_runtime::build_area_render_command(boundary_only_ir, std::nullopt, palette_colors)
           .has_value()) {
        return 8;
    }

    return 0;
}
