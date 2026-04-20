#include "marine_chart/chart_runtime/instruction_ir.h"

int main() {
    marine_chart::chart_runtime::InstructionIR point_symbol_ir;
    point_symbol_ir.kind = marine_chart::chart_runtime::InstructionKind::point_symbol;
    point_symbol_ir.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    point_symbol_ir.stable_id = "point:ACHARE:1";
    point_symbol_ir.source.object_class = "ACHARE";
    point_symbol_ir.source.lookup_type = "Point";
    point_symbol_ir.source.table_name = "Simplified";
    point_symbol_ir.source.lookup_id = "123";
    point_symbol_ir.source.raw_instruction = "SY(ACHARE02)";
    if(!point_symbol_ir.valid()) {
        return 1;
    }

    marine_chart::chart_runtime::InstructionIR invalid_ir = point_symbol_ir;
    invalid_ir.kind = marine_chart::chart_runtime::InstructionKind::unknown;
    if(invalid_ir.valid()) {
        return 2;
    }

    invalid_ir = point_symbol_ir;
    invalid_ir.primitive = marine_chart::chart_runtime::PrimitiveKind::unknown;
    if(invalid_ir.valid()) {
        return 3;
    }

    invalid_ir = point_symbol_ir;
    invalid_ir.stable_id.clear();
    if(invalid_ir.valid()) {
        return 4;
    }

    invalid_ir = point_symbol_ir;
    invalid_ir.source.lookup_id.clear();
    if(invalid_ir.valid()) {
        return 5;
    }

    return 0;
}
