#include "marine_chart/chart_runtime/text_layout.h"

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
    tx_rule_ir.instruction_text = "TX( OBJNAM , 1 , 2 , 3 , '15110' , 0 , 0 , CHBLK , 26 )";

    const auto tx_layout = marine_chart::chart_runtime::parse_text_layout(tx_rule_ir);
    if(!tx_layout.has_value() || tx_layout->rule_kind != marine_chart::chart_runtime::TextRuleKind::tx
        || tx_layout->attribute_name != "OBJNAM"
        || tx_layout->horizontal_justification_code != 1
        || tx_layout->vertical_justification_code != 2
        || tx_layout->spacing_code != 3
        || tx_layout->font_reference != "15110"
        || tx_layout->x_offset != 0
        || tx_layout->y_offset != 0
        || tx_layout->color_token != "CHBLK"
        || tx_layout->display_parameter != 26) {
        return 1;
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
    if(!te_layout.has_value() || te_layout->rule_kind != marine_chart::chart_runtime::TextRuleKind::te
        || te_layout->format_string != "%s"
        || te_layout->attribute_name != "OBJNAM"
        || te_layout->horizontal_justification_code != 3
        || te_layout->vertical_justification_code != 1
        || te_layout->spacing_code != 2
        || te_layout->font_reference != "15110"
        || te_layout->x_offset != 1
        || te_layout->y_offset != 0
        || te_layout->color_token != "CHBLK"
        || te_layout->display_parameter != 29) {
        return 2;
    }

    marine_chart::chart_runtime::TextRuleIR wrong_kind_ir = tx_rule_ir;
    wrong_kind_ir.instruction_text = "TE('%s','OBJNAM',3,1,2,'15110',1,0,CHBLK,29)";
    if(marine_chart::chart_runtime::parse_text_layout(wrong_kind_ir).has_value()) {
        return 3;
    }

    marine_chart::chart_runtime::TextRuleIR malformed_ir = tx_rule_ir;
    malformed_ir.instruction_text = "TX(OBJNAM,1,2,'15110',0,0,CHBLK,26)";
    if(marine_chart::chart_runtime::parse_text_layout(malformed_ir).has_value()) {
        return 4;
    }

    malformed_ir = te_rule_ir;
    malformed_ir.instruction_text = "TE('%s','OBJNAM',3,1,2,'15110',one,0,CHBLK,29)";
    if(marine_chart::chart_runtime::parse_text_layout(malformed_ir).has_value()) {
        return 5;
    }

    return 0;
}
