#include "marine_chart/chart_runtime/line_style_parser.h"

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

    const auto parsed_dash = marine_chart::chart_runtime::parse_line_style(line_style_ir);
    if(!parsed_dash.has_value() || parsed_dash->style_name != "DASH" || parsed_dash->width != 2
        || parsed_dash->color_token != "CHMGD") {
        return 1;
    }

    marine_chart::chart_runtime::LineStyleIR mixed_instruction_ir = line_style_ir;
    mixed_instruction_ir.instruction.source.raw_instruction = "LS(SOLD,5,CHGRD);SY(BRIDGE01)";
    mixed_instruction_ir.line_style_name = "SOLD";
    const auto parsed_sold = marine_chart::chart_runtime::parse_line_style(mixed_instruction_ir);
    if(!parsed_sold.has_value() || parsed_sold->style_name != "SOLD" || parsed_sold->width != 5
        || parsed_sold->color_token != "CHGRD") {
        return 2;
    }

    marine_chart::chart_runtime::LineStyleIR invalid_ir = line_style_ir;
    invalid_ir.instruction.source.raw_instruction = "SY(BRIDGE01)";
    if(marine_chart::chart_runtime::parse_line_style(invalid_ir).has_value()) {
        return 3;
    }

    invalid_ir = line_style_ir;
    invalid_ir.instruction.source.raw_instruction = "LS(DASH,abc,CHMGD)";
    if(marine_chart::chart_runtime::parse_line_style(invalid_ir).has_value()) {
        return 4;
    }

    return 0;
}
