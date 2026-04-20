#pragma once

#include "marine_chart/chart_runtime/instruction_ir.h"

#include <string>

namespace marine_chart::chart_runtime {

struct LineStyleIR final {
    InstructionIR instruction;
    std::string line_style_name;

    [[nodiscard]] bool valid() const noexcept {
        return instruction.valid() && instruction.kind == InstructionKind::line_style
            && instruction.primitive == PrimitiveKind::line && !line_style_name.empty();
    }

    bool operator==(const LineStyleIR&) const noexcept = default;
};

}  // namespace marine_chart::chart_runtime
