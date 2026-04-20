#include "marine_chart/chart_runtime/text_renderer.h"

int main() {
    marine_chart::chart_runtime::TextRuleIR tx_rule_ir;
    tx_rule_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::text_rule;
    tx_rule_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::area;
    tx_rule_ir.instruction.stable_id = "text-rule:SEAARE:88:0";
    tx_rule_ir.instruction.source.object_class = "SEAARE";
    tx_rule_ir.instruction.source.lookup_type = "Area";
    tx_rule_ir.instruction.source.table_name = "Plain";
    tx_rule_ir.instruction.source.lookup_id = "88";
    tx_rule_ir.rule_kind = marine_chart::chart_runtime::TextRuleKind::tx;
    tx_rule_ir.instruction_text = "TX(OBJNAM,1,2,3,'15110',0,0,CHBLK,26)";

    const auto tx_layout = marine_chart::chart_runtime::parse_text_layout(tx_rule_ir);
    if(!tx_layout.has_value()) {
        return 1;
    }

    marine_chart::chart_runtime::RuntimePaletteColors palette_colors;
    palette_colors.palette_name = "DAY_BRIGHT";
    palette_colors.graphics_file_name = "rastersymbols-day.png";
    palette_colors.entries.emplace("CHBLK", marine_chart::chart_runtime::make_runtime_color(24, 24, 24));

    const auto tx_command =
        marine_chart::chart_runtime::build_text_render_command(tx_rule_ir, *tx_layout, palette_colors);
    if(!tx_command.has_value() || tx_command->instruction_id != "text-rule:SEAARE:88:0"
        || tx_command->rule_kind != marine_chart::chart_runtime::TextRuleKind::tx
        || tx_command->attribute_name != "OBJNAM"
        || !tx_command->format_string.empty()
        || tx_command->font_reference != "15110"
        || tx_command->text_color != marine_chart::chart_runtime::make_runtime_color(24, 24, 24)
        || tx_command->display_parameter != 26) {
        return 2;
    }

    marine_chart::chart_runtime::TextRuleIR te_rule_ir = tx_rule_ir;
    te_rule_ir.instruction.stable_id = "text-rule:LIGHTS:77:0";
    te_rule_ir.instruction.source.object_class = "LIGHTS";
    te_rule_ir.instruction.source.lookup_type = "Point";
    te_rule_ir.instruction.source.table_name = "Simplified";
    te_rule_ir.instruction.source.lookup_id = "77";
    te_rule_ir.rule_kind = marine_chart::chart_runtime::TextRuleKind::te;
    te_rule_ir.instruction_text = "TE('%s','OBJNAM',3,1,2,'15110',1,0,CHBLK,29)";

    const auto te_layout = marine_chart::chart_runtime::parse_text_layout(te_rule_ir);
    if(!te_layout.has_value()) {
        return 3;
    }

    const auto te_command =
        marine_chart::chart_runtime::build_text_render_command(te_rule_ir, *te_layout, palette_colors);
    if(!te_command.has_value() || te_command->rule_kind != marine_chart::chart_runtime::TextRuleKind::te
        || te_command->format_string != "%s"
        || te_command->attribute_name != "OBJNAM"
        || te_command->horizontal_justification_code != 3
        || te_command->x_offset != 1
        || te_command->display_parameter != 29) {
        return 4;
    }

    marine_chart::chart_runtime::TextLayout wrong_layout = *tx_layout;
    if(marine_chart::chart_runtime::build_text_render_command(te_rule_ir, wrong_layout, palette_colors).has_value()) {
        return 5;
    }

    marine_chart::chart_runtime::RuntimePaletteColors missing_color_palette = palette_colors;
    missing_color_palette.entries.clear();
    if(marine_chart::chart_runtime::build_text_render_command(tx_rule_ir, *tx_layout, missing_color_palette)
           .has_value()) {
        return 6;
    }

    return 0;
}
