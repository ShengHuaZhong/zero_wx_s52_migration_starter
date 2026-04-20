#include "marine_chart/chart_runtime/line_style_ir.h"

int main() {
    marine_chart::chart_runtime::LineStyleIR line_style_ir;
    line_style_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::line_style;
    line_style_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::line;
    line_style_ir.instruction.stable_id = "line:TRFLNE:1";
    line_style_ir.instruction.source.object_class = "TRFLNE";
    line_style_ir.instruction.source.lookup_type = "Line";
    line_style_ir.instruction.source.table_name = "Lines";
    line_style_ir.instruction.source.lookup_id = "12";
    line_style_ir.instruction.source.raw_instruction = "LS(DASH,2,CHMGD)";
    line_style_ir.line_style_name = "DASH";
    if(!line_style_ir.valid()) {
        return 1;
    }

    marine_chart::chart_runtime::LineStyleIR invalid_ir = line_style_ir;
    invalid_ir.line_style_name.clear();
    if(invalid_ir.valid()) {
        return 2;
    }

    invalid_ir = line_style_ir;
    invalid_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::point_symbol;
    if(invalid_ir.valid()) {
        return 3;
    }

    invalid_ir = line_style_ir;
    invalid_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::area;
    if(invalid_ir.valid()) {
        return 4;
    }

    return 0;
}
