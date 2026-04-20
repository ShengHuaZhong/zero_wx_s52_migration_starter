#include "marine_chart/chart_runtime/runtime_render_frame.h"
#include "marine_chart/s52_core_headless/headless_core_init.h"

int main() {
    const auto initialization = marine_chart::s52_core_headless::initialize_headless_core("vendor/opencpn_s57data");
    if(!initialization.has_value() || !initialization->valid()) {
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

    marine_chart::chart_runtime::PointSymbolIR missing_point_symbol_ir = point_symbol_ir;
    missing_point_symbol_ir.instruction.stable_id = "point-symbol:UNKNOWN:99";
    missing_point_symbol_ir.instruction.source.object_class = "UNKNOWN";
    missing_point_symbol_ir.instruction.source.lookup_id = "99";
    missing_point_symbol_ir.symbol_name = "UNKNOWN01";
    buffer.point_symbols.push_back(missing_point_symbol_ir);

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
    buffer.line_styles.push_back(line_style_ir);

    marine_chart::chart_runtime::AreaPatternIR area_pattern_ir;
    area_pattern_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::area_pattern;
    area_pattern_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::area;
    area_pattern_ir.instruction.stable_id = "area-pattern:AIRARE:77";
    area_pattern_ir.instruction.source.object_class = "AIRARE";
    area_pattern_ir.instruction.source.lookup_type = "Area";
    area_pattern_ir.instruction.source.table_name = "Plain";
    area_pattern_ir.instruction.source.lookup_id = "77";
    area_pattern_ir.fill_color_token = "AREAFILL";
    area_pattern_ir.pattern_name = "AIRARE02";
    area_pattern_ir.boundary_line_style_name = "SOLD";
    buffer.area_patterns.push_back(area_pattern_ir);

    marine_chart::chart_runtime::TextRuleIR text_rule_ir;
    text_rule_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::text_rule;
    text_rule_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::area;
    text_rule_ir.instruction.stable_id = "text-rule:SEAARE:88:0";
    text_rule_ir.instruction.source.object_class = "SEAARE";
    text_rule_ir.instruction.source.lookup_type = "Area";
    text_rule_ir.instruction.source.table_name = "Plain";
    text_rule_ir.instruction.source.lookup_id = "88";
    text_rule_ir.rule_kind = marine_chart::chart_runtime::TextRuleKind::tx;
    text_rule_ir.instruction_text = "TX(OBJNAM,1,2,3,'15110',0,0,CHBLK,26)";
    buffer.text_rules.push_back(text_rule_ir);

    marine_chart::chart_runtime::DisplayPriorityIR area_priority_ir;
    area_priority_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::display_priority;
    area_priority_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::area;
    area_priority_ir.instruction.stable_id = "display-priority:AIRARE:77";
    area_priority_ir.instruction.source.object_class = "AIRARE";
    area_priority_ir.instruction.source.lookup_type = "Area";
    area_priority_ir.instruction.source.table_name = "Plain";
    area_priority_ir.instruction.source.lookup_id = "77";
    area_priority_ir.group = marine_chart::chart_runtime::DisplayPriorityGroup::area_1;
    area_priority_ir.sort_rank = 2;
    area_priority_ir.source_name = "Area 1";
    buffer.display_priorities.push_back(area_priority_ir);

    marine_chart::chart_runtime::DisplayPriorityIR missing_point_priority_ir;
    missing_point_priority_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::display_priority;
    missing_point_priority_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    missing_point_priority_ir.instruction.stable_id = "display-priority:UNKNOWN:99";
    missing_point_priority_ir.instruction.source.object_class = "UNKNOWN";
    missing_point_priority_ir.instruction.source.lookup_type = "Point";
    missing_point_priority_ir.instruction.source.table_name = "Simplified";
    missing_point_priority_ir.instruction.source.lookup_id = "99";
    missing_point_priority_ir.group = marine_chart::chart_runtime::DisplayPriorityGroup::routing;
    missing_point_priority_ir.sort_rank = 7;
    missing_point_priority_ir.source_name = "Routing";
    buffer.display_priorities.push_back(missing_point_priority_ir);

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
    text_priority_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::area;
    text_priority_ir.instruction.stable_id = "display-priority:SEAARE:88";
    text_priority_ir.instruction.source.object_class = "SEAARE";
    text_priority_ir.instruction.source.lookup_type = "Area";
    text_priority_ir.instruction.source.table_name = "Plain";
    text_priority_ir.instruction.source.lookup_id = "88";
    text_priority_ir.group = marine_chart::chart_runtime::DisplayPriorityGroup::mariners;
    text_priority_ir.sort_rank = 9;
    text_priority_ir.source_name = "Mariners";
    buffer.display_priorities.push_back(text_priority_ir);

    const auto point_atlas_entry =
        marine_chart::chart_runtime::load_point_symbol_atlas_entry(initialization->asset_catalogs, "DAY_BRIGHT", point_symbol_ir);
    const auto pattern_atlas_entry =
        marine_chart::chart_runtime::load_pattern_atlas_entry(initialization->asset_catalogs, "DAY_BRIGHT", area_pattern_ir);
    if(!point_atlas_entry.has_value() || !pattern_atlas_entry.has_value()) {
        return 2;
    }

    marine_chart::chart_runtime::RuntimePaletteColors palette_colors;
    palette_colors.palette_name = "DAY_BRIGHT";
    palette_colors.graphics_file_name = "rastersymbols-day.png";
    palette_colors.entries.insert_or_assign(
        point_atlas_entry->color_token,
        marine_chart::chart_runtime::make_runtime_color(18, 18, 18));
    palette_colors.entries.insert_or_assign("CHMGD", marine_chart::chart_runtime::make_runtime_color(153, 102, 51));
    palette_colors.entries.insert_or_assign("AREAFILL", marine_chart::chart_runtime::make_runtime_color(210, 220, 230));
    palette_colors.entries.insert_or_assign(
        pattern_atlas_entry->color_token,
        marine_chart::chart_runtime::make_runtime_color(44, 88, 132));
    palette_colors.entries.insert_or_assign("CHBLK", marine_chart::chart_runtime::make_runtime_color(24, 24, 24));

    const auto frame = marine_chart::chart_runtime::build_runtime_render_frame(
        buffer,
        initialization->asset_catalogs,
        palette_colors);
    if(frame.empty() || frame.command_count() != 4 || frame.point_commands.size() != 1 || frame.line_commands.size() != 1
        || frame.area_commands.size() != 1 || frame.text_commands.size() != 1 || frame.sorted_instructions.size() != 4) {
        return 3;
    }

    if(frame.point_commands.front().instruction_id != "point-symbol:ACHPNT:42"
        || frame.line_commands.front().instruction_id != "line-style:TRFLNE:12"
        || frame.area_commands.front().instruction_id != "area-pattern:AIRARE:77"
        || frame.text_commands.front().instruction_id != "text-rule:SEAARE:88:0") {
        return 4;
    }

    if(frame.sorted_instructions[0].instruction_id != "area-pattern:AIRARE:77"
        || frame.sorted_instructions[1].instruction_id != "line-style:TRFLNE:12"
        || frame.sorted_instructions[2].instruction_id != "point-symbol:ACHPNT:42"
        || frame.sorted_instructions[3].instruction_id != "text-rule:SEAARE:88:0") {
        return 5;
    }

    for(const auto& sorted_instruction : frame.sorted_instructions) {
        if(sorted_instruction.instruction_id == "point-symbol:UNKNOWN:99") {
            return 6;
        }
    }

    marine_chart::chart_runtime::RuntimePaletteColors empty_palette = palette_colors;
    empty_palette.entries.clear();
    if(!marine_chart::chart_runtime::build_runtime_render_frame(buffer, initialization->asset_catalogs, empty_palette)
            .empty()) {
        return 7;
    }

    return 0;
}
