#include "marine_chart/chart_runtime/point_renderer.h"
#include "marine_chart/s52_core_headless/headless_core_init.h"

int main() {
    const auto initialization = marine_chart::s52_core_headless::initialize_headless_core("vendor/opencpn_s57data");
    if(!initialization.has_value() || !initialization->valid()) {
        return 1;
    }

    marine_chart::chart_runtime::PointSymbolIR point_symbol_ir;
    point_symbol_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::point_symbol;
    point_symbol_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    point_symbol_ir.instruction.stable_id = "point-symbol:ACHPNT:42";
    point_symbol_ir.instruction.source.object_class = "ACHPNT";
    point_symbol_ir.instruction.source.lookup_type = "Point";
    point_symbol_ir.instruction.source.table_name = "Simplified";
    point_symbol_ir.instruction.source.lookup_id = "42";
    point_symbol_ir.symbol_name = "ACHPNT01";

    const auto atlas_entry =
        marine_chart::chart_runtime::load_point_symbol_atlas_entry(initialization->asset_catalogs, "DAY_BRIGHT", point_symbol_ir);
    if(!atlas_entry.has_value()) {
        return 2;
    }

    marine_chart::chart_runtime::RuntimePaletteColors palette_colors;
    palette_colors.palette_name = "DAY_BRIGHT";
    palette_colors.graphics_file_name = "rastersymbols-day.png";
    palette_colors.entries.emplace(atlas_entry->color_token, marine_chart::chart_runtime::make_runtime_color(18, 18, 18));

    const auto render_command =
        marine_chart::chart_runtime::build_point_render_command(point_symbol_ir, *atlas_entry, palette_colors);
    if(!render_command.has_value()
        || render_command->instruction_id != "point-symbol:ACHPNT:42"
        || render_command->symbol_name != "ACHPNT01"
        || render_command->graphics_file_name != "rastersymbols-day.png"
        || render_command->source_width <= 0
        || render_command->source_height <= 0
        || render_command->tint_color != marine_chart::chart_runtime::make_runtime_color(18, 18, 18)) {
        return 3;
    }

    marine_chart::chart_runtime::RuntimePaletteColors wrong_palette = palette_colors;
    wrong_palette.palette_name = "DAY";
    if(marine_chart::chart_runtime::build_point_render_command(point_symbol_ir, *atlas_entry, wrong_palette).has_value()) {
        return 4;
    }

    marine_chart::chart_runtime::RuntimePaletteColors missing_color_palette = palette_colors;
    missing_color_palette.entries.clear();
    if(marine_chart::chart_runtime::build_point_render_command(point_symbol_ir, *atlas_entry, missing_color_palette)
           .has_value()) {
        return 5;
    }

    return 0;
}
