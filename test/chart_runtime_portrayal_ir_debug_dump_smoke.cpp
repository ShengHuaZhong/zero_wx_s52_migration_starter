#include "marine_chart/chart_runtime/portrayal_ir_debug_dump.h"

int main() {
    marine_chart::chart_runtime::FeaturePortrayalIR portrayal_ir;

    marine_chart::chart_runtime::PointSymbolIR point_symbol_ir;
    point_symbol_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::point_symbol;
    point_symbol_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    point_symbol_ir.instruction.stable_id = "point-symbol:ACHPNT:42";
    point_symbol_ir.instruction.source.object_class = "ACHPNT";
    point_symbol_ir.instruction.source.lookup_type = "Point";
    point_symbol_ir.instruction.source.table_name = "Simplified";
    point_symbol_ir.instruction.source.lookup_id = "42";
    point_symbol_ir.symbol_name = "ACHPNT01";
    portrayal_ir.point_symbols.push_back(point_symbol_ir);

    marine_chart::chart_runtime::DisplayPriorityIR display_priority_ir;
    display_priority_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::display_priority;
    display_priority_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    display_priority_ir.instruction.stable_id = "display-priority:ACHPNT:42";
    display_priority_ir.instruction.source.object_class = "ACHPNT";
    display_priority_ir.instruction.source.lookup_type = "Point";
    display_priority_ir.instruction.source.table_name = "Simplified";
    display_priority_ir.instruction.source.lookup_id = "42";
    display_priority_ir.group = marine_chart::chart_runtime::DisplayPriorityGroup::hazards;
    display_priority_ir.sort_rank = 8;
    display_priority_ir.source_name = "Hazards";
    portrayal_ir.display_priorities.push_back(display_priority_ir);

    const auto dump = marine_chart::chart_runtime::dump_feature_portrayal_ir(portrayal_ir);
    if(dump.find("feature_portrayal_ir") == std::string::npos) {
        return 1;
    }

    if(dump.find("point_symbols: 1") == std::string::npos || dump.find("symbol=ACHPNT01") == std::string::npos) {
        return 2;
    }

    if(dump.find("display_priorities: 1") == std::string::npos || dump.find("sort_rank=8") == std::string::npos) {
        return 3;
    }

    if(dump.find("line_styles: 0") == std::string::npos || dump.find("area_patterns: 0") == std::string::npos
        || dump.find("text_rules: 0") == std::string::npos) {
        return 4;
    }

    return 0;
}
