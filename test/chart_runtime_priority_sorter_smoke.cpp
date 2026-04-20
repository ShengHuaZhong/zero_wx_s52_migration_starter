#include "marine_chart/chart_runtime/priority_sorter.h"

int main() {
    marine_chart::chart_runtime::RuntimePortrayalBuffer empty_buffer;
    if(!marine_chart::chart_runtime::sort_render_instructions_by_priority(empty_buffer).empty()) {
        return 1;
    }

    marine_chart::chart_runtime::RuntimePortrayalBuffer buffer;

    marine_chart::chart_runtime::PointSymbolIR point_symbol_ir;
    point_symbol_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::point_symbol;
    point_symbol_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    point_symbol_ir.instruction.stable_id = "point-symbol:ACHPNT:42";
    point_symbol_ir.instruction.source.object_class = "ACHPNT";
    point_symbol_ir.instruction.source.lookup_type = "Point";
    point_symbol_ir.instruction.source.table_name = "Simplified";
    point_symbol_ir.instruction.source.lookup_id = "42";
    point_symbol_ir.symbol_name = "ACHPNT01";
    buffer.point_symbols.push_back(point_symbol_ir);

    marine_chart::chart_runtime::PointSymbolIR missing_priority_point_ir = point_symbol_ir;
    missing_priority_point_ir.instruction.stable_id = "point-symbol:MIPARE:99";
    missing_priority_point_ir.instruction.source.object_class = "MIPARE";
    missing_priority_point_ir.instruction.source.lookup_id = "99";
    missing_priority_point_ir.symbol_name = "MIPARE01";
    buffer.point_symbols.push_back(missing_priority_point_ir);

    marine_chart::chart_runtime::LineStyleIR line_style_ir;
    line_style_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::line_style;
    line_style_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::line;
    line_style_ir.instruction.stable_id = "line-style:TRFLNE:12";
    line_style_ir.instruction.source.object_class = "TRFLNE";
    line_style_ir.instruction.source.lookup_type = "Line";
    line_style_ir.instruction.source.table_name = "Lines";
    line_style_ir.instruction.source.lookup_id = "12";
    line_style_ir.line_style_name = "DASH";
    buffer.line_styles.push_back(line_style_ir);

    marine_chart::chart_runtime::AreaPatternIR area_pattern_ir;
    area_pattern_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::area_pattern;
    area_pattern_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::area;
    area_pattern_ir.instruction.stable_id = "area-pattern:SEAARE:19";
    area_pattern_ir.instruction.source.object_class = "SEAARE";
    area_pattern_ir.instruction.source.lookup_type = "Area";
    area_pattern_ir.instruction.source.table_name = "Plain";
    area_pattern_ir.instruction.source.lookup_id = "19";
    area_pattern_ir.fill_color_token = "DEPVS";
    buffer.area_patterns.push_back(area_pattern_ir);

    marine_chart::chart_runtime::TextRuleIR text_rule_ir;
    text_rule_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::text_rule;
    text_rule_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    text_rule_ir.instruction.stable_id = "text-rule:LIGHTS:77:0";
    text_rule_ir.instruction.source.object_class = "LIGHTS";
    text_rule_ir.instruction.source.lookup_type = "Point";
    text_rule_ir.instruction.source.table_name = "Simplified";
    text_rule_ir.instruction.source.lookup_id = "77";
    text_rule_ir.rule_kind = marine_chart::chart_runtime::TextRuleKind::tx;
    text_rule_ir.instruction_text = "TX(OBJNAM,1,2,3,'15110',0,0,CHBLK,26)";
    buffer.text_rules.push_back(text_rule_ir);

    marine_chart::chart_runtime::DisplayPriorityIR area_priority_ir;
    area_priority_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::display_priority;
    area_priority_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::area;
    area_priority_ir.instruction.stable_id = "display-priority:SEAARE:19";
    area_priority_ir.instruction.source.object_class = "SEAARE";
    area_priority_ir.instruction.source.lookup_type = "Area";
    area_priority_ir.instruction.source.table_name = "Plain";
    area_priority_ir.instruction.source.lookup_id = "19";
    area_priority_ir.group = marine_chart::chart_runtime::DisplayPriorityGroup::area_1;
    area_priority_ir.sort_rank = 2;
    area_priority_ir.source_name = "Area 1";
    buffer.display_priorities.push_back(area_priority_ir);

    marine_chart::chart_runtime::DisplayPriorityIR point_priority_ir;
    point_priority_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::display_priority;
    point_priority_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    point_priority_ir.instruction.stable_id = "display-priority:ACHPNT:42";
    point_priority_ir.instruction.source.object_class = "ACHPNT";
    point_priority_ir.instruction.source.lookup_type = "Point";
    point_priority_ir.instruction.source.table_name = "Simplified";
    point_priority_ir.instruction.source.lookup_id = "42";
    point_priority_ir.group = marine_chart::chart_runtime::DisplayPriorityGroup::hazards;
    point_priority_ir.sort_rank = 8;
    point_priority_ir.source_name = "Hazards";
    buffer.display_priorities.push_back(point_priority_ir);

    marine_chart::chart_runtime::DisplayPriorityIR line_priority_ir;
    line_priority_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::display_priority;
    line_priority_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::line;
    line_priority_ir.instruction.stable_id = "display-priority:TRFLNE:12";
    line_priority_ir.instruction.source.object_class = "TRFLNE";
    line_priority_ir.instruction.source.lookup_type = "Line";
    line_priority_ir.instruction.source.table_name = "Lines";
    line_priority_ir.instruction.source.lookup_id = "12";
    line_priority_ir.group = marine_chart::chart_runtime::DisplayPriorityGroup::area_symbol;
    line_priority_ir.sort_rank = 6;
    line_priority_ir.source_name = "Area Symbol";
    buffer.display_priorities.push_back(line_priority_ir);

    marine_chart::chart_runtime::DisplayPriorityIR text_priority_ir;
    text_priority_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::display_priority;
    text_priority_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    text_priority_ir.instruction.stable_id = "display-priority:LIGHTS:77";
    text_priority_ir.instruction.source.object_class = "LIGHTS";
    text_priority_ir.instruction.source.lookup_type = "Point";
    text_priority_ir.instruction.source.table_name = "Simplified";
    text_priority_ir.instruction.source.lookup_id = "77";
    text_priority_ir.group = marine_chart::chart_runtime::DisplayPriorityGroup::mariners;
    text_priority_ir.sort_rank = 9;
    text_priority_ir.source_name = "Mariners";
    buffer.display_priorities.push_back(text_priority_ir);

    const auto sorted_instructions = marine_chart::chart_runtime::sort_render_instructions_by_priority(buffer);
    if(sorted_instructions.size() != 4) {
        return 2;
    }

    if(!sorted_instructions[0].valid() || sorted_instructions[0].instruction_id != "area-pattern:SEAARE:19"
        || sorted_instructions[0].sort_rank != 2
        || sorted_instructions[0].group != marine_chart::chart_runtime::DisplayPriorityGroup::area_1) {
        return 3;
    }

    if(sorted_instructions[1].instruction_id != "line-style:TRFLNE:12" || sorted_instructions[1].sort_rank != 6
        || sorted_instructions[1].priority_source_name != "Area Symbol") {
        return 4;
    }

    if(sorted_instructions[2].instruction_id != "point-symbol:ACHPNT:42" || sorted_instructions[2].sort_rank != 8
        || sorted_instructions[2].group != marine_chart::chart_runtime::DisplayPriorityGroup::hazards) {
        return 5;
    }

    if(sorted_instructions[3].instruction_id != "text-rule:LIGHTS:77:0" || sorted_instructions[3].sort_rank != 9
        || sorted_instructions[3].priority_source_name != "Mariners") {
        return 6;
    }

    return 0;
}
