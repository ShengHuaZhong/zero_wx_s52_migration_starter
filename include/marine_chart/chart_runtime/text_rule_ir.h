#pragma once

#include "marine_chart/chart_runtime/instruction_ir.h"

#include <string>

namespace marine_chart::chart_runtime {

enum class TextRuleKind {
    unknown,
    tx,
    te
};

struct TextRuleIR final {
    InstructionIR instruction;
    TextRuleKind rule_kind{TextRuleKind::unknown};
    std::string instruction_text;

    [[nodiscard]] bool valid() const noexcept {
        return instruction.valid() && instruction.kind == InstructionKind::text_rule
            && instruction.primitive != PrimitiveKind::unknown && rule_kind != TextRuleKind::unknown
            && !instruction_text.empty();
    }

    bool operator==(const TextRuleIR&) const noexcept = default;
};

}  // namespace marine_chart::chart_runtime
