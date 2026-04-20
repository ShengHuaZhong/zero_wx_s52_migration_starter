#include "marine_chart/chart_runtime/portrayal_ir_ingestion.h"

int main() {
    marine_chart::chart_runtime::FeaturePortrayalIR first_feature_ir;

    marine_chart::chart_runtime::PointSymbolIR point_symbol_ir;
    point_symbol_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::point_symbol;
    point_symbol_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    point_symbol_ir.instruction.stable_id = "point-symbol:ACHPNT:42";
    point_symbol_ir.instruction.source.object_class = "ACHPNT";
    point_symbol_ir.instruction.source.lookup_type = "Point";
    point_symbol_ir.instruction.source.table_name = "Simplified";
    point_symbol_ir.instruction.source.lookup_id = "42";
    point_symbol_ir.symbol_name = "ACHPNT01";
    first_feature_ir.point_symbols.push_back(point_symbol_ir);

    marine_chart::chart_runtime::DisplayPriorityIR first_priority_ir;
    first_priority_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::display_priority;
    first_priority_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    first_priority_ir.instruction.stable_id = "display-priority:ACHPNT:42";
    first_priority_ir.instruction.source.object_class = "ACHPNT";
    first_priority_ir.instruction.source.lookup_type = "Point";
    first_priority_ir.instruction.source.table_name = "Simplified";
    first_priority_ir.instruction.source.lookup_id = "42";
    first_priority_ir.group = marine_chart::chart_runtime::DisplayPriorityGroup::hazards;
    first_priority_ir.sort_rank = 8;
    first_priority_ir.source_name = "Hazards";
    first_feature_ir.display_priorities.push_back(first_priority_ir);

    marine_chart::chart_runtime::FeaturePortrayalIR second_feature_ir;

    marine_chart::chart_runtime::LineStyleIR line_style_ir;
    line_style_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::line_style;
    line_style_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::line;
    line_style_ir.instruction.stable_id = "line-style:TRFLNE:12";
    line_style_ir.instruction.source.object_class = "TRFLNE";
    line_style_ir.instruction.source.lookup_type = "Line";
    line_style_ir.instruction.source.table_name = "Lines";
    line_style_ir.instruction.source.lookup_id = "12";
    line_style_ir.line_style_name = "DASH";
    second_feature_ir.line_styles.push_back(line_style_ir);

    marine_chart::chart_runtime::DisplayPriorityIR second_priority_ir;
    second_priority_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::display_priority;
    second_priority_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::line;
    second_priority_ir.instruction.stable_id = "display-priority:TRFLNE:12";
    second_priority_ir.instruction.source.object_class = "TRFLNE";
    second_priority_ir.instruction.source.lookup_type = "Line";
    second_priority_ir.instruction.source.table_name = "Lines";
    second_priority_ir.instruction.source.lookup_id = "12";
    second_priority_ir.group = marine_chart::chart_runtime::DisplayPriorityGroup::area_symbol;
    second_priority_ir.sort_rank = 6;
    second_priority_ir.source_name = "Area Symbol";
    second_feature_ir.display_priorities.push_back(second_priority_ir);

    marine_chart::chart_runtime::RuntimePortrayalBuffer buffer;
    if(!buffer.empty() || buffer.instruction_count() != 0) {
        return 1;
    }

    marine_chart::chart_runtime::ingest_feature_portrayal_ir(buffer, first_feature_ir);
    marine_chart::chart_runtime::ingest_feature_portrayal_ir(buffer, second_feature_ir);

    if(buffer.point_symbols.size() != 1 || buffer.point_symbols.front().symbol_name != "ACHPNT01") {
        return 2;
    }

    if(buffer.line_styles.size() != 1 || buffer.line_styles.front().line_style_name != "DASH") {
        return 3;
    }

    if(buffer.display_priorities.size() != 2 || buffer.display_priorities.front().source_name != "Hazards"
        || buffer.display_priorities.back().source_name != "Area Symbol") {
        return 4;
    }

    if(buffer.instruction_count() != 4) {
        return 5;
    }

    return 0;
}
