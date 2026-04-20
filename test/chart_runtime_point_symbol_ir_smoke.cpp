#include "marine_chart/chart_runtime/point_symbol_ir.h"

int main() {
    marine_chart::chart_runtime::PointSymbolIR point_symbol_ir;
    point_symbol_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::point_symbol;
    point_symbol_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    point_symbol_ir.instruction.stable_id = "point:ACHPNT:1";
    point_symbol_ir.instruction.source.object_class = "ACHPNT";
    point_symbol_ir.instruction.source.lookup_type = "Point";
    point_symbol_ir.instruction.source.table_name = "Simplified";
    point_symbol_ir.instruction.source.lookup_id = "42";
    point_symbol_ir.instruction.source.raw_instruction = "SY(ACHPNT01)";
    point_symbol_ir.symbol_name = "ACHPNT01";
    if(!point_symbol_ir.valid()) {
        return 1;
    }

    marine_chart::chart_runtime::PointSymbolIR invalid_ir = point_symbol_ir;
    invalid_ir.symbol_name.clear();
    if(invalid_ir.valid()) {
        return 2;
    }

    invalid_ir = point_symbol_ir;
    invalid_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::line_style;
    if(invalid_ir.valid()) {
        return 3;
    }

    invalid_ir = point_symbol_ir;
    invalid_ir.instruction.stable_id.clear();
    if(invalid_ir.valid()) {
        return 4;
    }

    return 0;
}
