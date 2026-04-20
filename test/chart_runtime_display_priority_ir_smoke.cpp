#include "marine_chart/chart_runtime/display_priority_ir.h"

int main() {
    marine_chart::chart_runtime::DisplayPriorityIR display_priority_ir;
    display_priority_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::display_priority;
    display_priority_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::area;
    display_priority_ir.instruction.stable_id = "priority:SEAARE:1";
    display_priority_ir.instruction.source.object_class = "SEAARE";
    display_priority_ir.instruction.source.lookup_type = "Area";
    display_priority_ir.instruction.source.table_name = "Plain";
    display_priority_ir.instruction.source.lookup_id = "19";
    display_priority_ir.instruction.source.raw_instruction = "TX(OBJNAM,1,2,3,'15110',0,0,CHBLK,26)";
    display_priority_ir.group = marine_chart::chart_runtime::DisplayPriorityGroup::area_2;
    display_priority_ir.sort_rank = 3;
    display_priority_ir.source_name = "Area 2";
    if(!display_priority_ir.valid()) {
        return 1;
    }

    marine_chart::chart_runtime::DisplayPriorityIR point_priority_ir = display_priority_ir;
    point_priority_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    point_priority_ir.group = marine_chart::chart_runtime::DisplayPriorityGroup::hazards;
    point_priority_ir.sort_rank = 8;
    point_priority_ir.source_name = "Hazards";
    if(!point_priority_ir.valid()) {
        return 2;
    }

    marine_chart::chart_runtime::DisplayPriorityIR invalid_ir = display_priority_ir;
    invalid_ir.group = marine_chart::chart_runtime::DisplayPriorityGroup::unknown;
    if(invalid_ir.valid()) {
        return 3;
    }

    invalid_ir = display_priority_ir;
    invalid_ir.sort_rank = -1;
    if(invalid_ir.valid()) {
        return 4;
    }

    invalid_ir = display_priority_ir;
    invalid_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::area_pattern;
    if(invalid_ir.valid()) {
        return 5;
    }

    return 0;
}
