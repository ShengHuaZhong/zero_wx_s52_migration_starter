#include "marine_chart/chart_runtime/text_rule_ir.h"

int main() {
    marine_chart::chart_runtime::TextRuleIR text_rule_ir;
    text_rule_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::text_rule;
    text_rule_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::area;
    text_rule_ir.instruction.stable_id = "text:SEAARE:1";
    text_rule_ir.instruction.source.object_class = "SEAARE";
    text_rule_ir.instruction.source.lookup_type = "Area";
    text_rule_ir.instruction.source.table_name = "Plain";
    text_rule_ir.instruction.source.lookup_id = "88";
    text_rule_ir.instruction.source.raw_instruction = "TX(OBJNAM,1,2,3,'15110',0,0,CHBLK,26)";
    text_rule_ir.rule_kind = marine_chart::chart_runtime::TextRuleKind::tx;
    text_rule_ir.instruction_text = "TX(OBJNAM,1,2,3,'15110',0,0,CHBLK,26)";
    if(!text_rule_ir.valid()) {
        return 1;
    }

    marine_chart::chart_runtime::TextRuleIR te_rule_ir = text_rule_ir;
    te_rule_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    te_rule_ir.rule_kind = marine_chart::chart_runtime::TextRuleKind::te;
    te_rule_ir.instruction_text = "TE('%s','OBJNAM',3,1,2,'15110',1,0,CHBLK,29)";
    if(!te_rule_ir.valid()) {
        return 2;
    }

    marine_chart::chart_runtime::TextRuleIR invalid_ir = text_rule_ir;
    invalid_ir.rule_kind = marine_chart::chart_runtime::TextRuleKind::unknown;
    if(invalid_ir.valid()) {
        return 3;
    }

    invalid_ir = text_rule_ir;
    invalid_ir.instruction_text.clear();
    if(invalid_ir.valid()) {
        return 4;
    }

    invalid_ir = text_rule_ir;
    invalid_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::point_symbol;
    if(invalid_ir.valid()) {
        return 5;
    }

    return 0;
}
