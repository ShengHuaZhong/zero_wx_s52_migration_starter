#include "marine_chart/chart_runtime/area_pattern_ir.h"

int main() {
    marine_chart::chart_runtime::AreaPatternIR area_pattern_ir;
    area_pattern_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::area_pattern;
    area_pattern_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::area;
    area_pattern_ir.instruction.stable_id = "area:UNSARE:1";
    area_pattern_ir.instruction.source.object_class = "UNSARE";
    area_pattern_ir.instruction.source.lookup_type = "Area";
    area_pattern_ir.instruction.source.table_name = "Plain";
    area_pattern_ir.instruction.source.lookup_id = "51";
    area_pattern_ir.instruction.source.raw_instruction = "AC(NODTA);AP(NODATA03);LS(SOLD,2,CHGRD)";
    area_pattern_ir.fill_color_token = "NODTA";
    area_pattern_ir.pattern_name = "NODATA03";
    area_pattern_ir.boundary_line_style_name = "SOLD";
    if(!area_pattern_ir.valid()) {
        return 1;
    }

    marine_chart::chart_runtime::AreaPatternIR boundary_only_ir = area_pattern_ir;
    boundary_only_ir.fill_color_token.clear();
    boundary_only_ir.pattern_name.clear();
    if(!boundary_only_ir.valid()) {
        return 2;
    }

    marine_chart::chart_runtime::AreaPatternIR invalid_ir = area_pattern_ir;
    invalid_ir.fill_color_token.clear();
    invalid_ir.pattern_name.clear();
    invalid_ir.boundary_line_style_name.clear();
    if(invalid_ir.valid()) {
        return 3;
    }

    invalid_ir = area_pattern_ir;
    invalid_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::line_style;
    if(invalid_ir.valid()) {
        return 4;
    }

    invalid_ir = area_pattern_ir;
    invalid_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::line;
    if(invalid_ir.valid()) {
        return 5;
    }

    return 0;
}
