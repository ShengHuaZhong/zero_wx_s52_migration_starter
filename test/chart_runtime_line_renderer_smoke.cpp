#include "marine_chart/chart_runtime/line_renderer.h"

int main() {
    marine_chart::chart_runtime::LineStyleIR line_style_ir;
    line_style_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::line_style;
    line_style_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::line;
    line_style_ir.instruction.stable_id = "line-style:TRFLNE:12";
    line_style_ir.instruction.source.object_class = "TRFLNE";
    line_style_ir.instruction.source.lookup_type = "Line";
    line_style_ir.instruction.source.table_name = "Lines";
    line_style_ir.instruction.source.lookup_id = "12";
    line_style_ir.instruction.source.raw_instruction = "LS(DASH,2,CHMGD)";
    line_style_ir.line_style_name = "DASH";

    const auto parsed_line_style = marine_chart::chart_runtime::parse_line_style(line_style_ir);
    if(!parsed_line_style.has_value()) {
        return 1;
    }

    marine_chart::chart_runtime::RuntimePaletteColors palette_colors;
    palette_colors.palette_name = "DAY_BRIGHT";
    palette_colors.graphics_file_name = "rastersymbols-day.png";
    palette_colors.entries.emplace("CHMGD", marine_chart::chart_runtime::make_runtime_color(153, 102, 51));

    const auto render_command =
        marine_chart::chart_runtime::build_line_render_command(line_style_ir, *parsed_line_style, palette_colors);
    if(!render_command.has_value()
        || render_command->instruction_id != "line-style:TRFLNE:12"
        || render_command->style_name != "DASH"
        || render_command->width != 2
        || render_command->stroke_color != marine_chart::chart_runtime::make_runtime_color(153, 102, 51)) {
        return 2;
    }

    marine_chart::chart_runtime::ParsedLineStyle wrong_style = *parsed_line_style;
    wrong_style.style_name = "SOLD";
    if(marine_chart::chart_runtime::build_line_render_command(line_style_ir, wrong_style, palette_colors).has_value()) {
        return 3;
    }

    marine_chart::chart_runtime::RuntimePaletteColors missing_color_palette = palette_colors;
    missing_color_palette.entries.clear();
    if(marine_chart::chart_runtime::build_line_render_command(line_style_ir, *parsed_line_style, missing_color_palette)
           .has_value()) {
        return 4;
    }

    return 0;
}
