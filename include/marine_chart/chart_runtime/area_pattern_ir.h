#pragma once

#include "marine_chart/chart_runtime/instruction_ir.h"

#include <string>

namespace marine_chart::chart_runtime {

struct AreaPatternIR final {
    InstructionIR instruction;
    std::string fill_color_token;
    std::string pattern_name;
    std::string boundary_line_style_name;

    [[nodiscard]] bool valid() const noexcept {
        return instruction.valid() && instruction.kind == InstructionKind::area_pattern
            && instruction.primitive == PrimitiveKind::area
            && (!fill_color_token.empty() || !pattern_name.empty() || !boundary_line_style_name.empty());
    }

    bool operator==(const AreaPatternIR&) const noexcept = default;
};

}  // namespace marine_chart::chart_runtime
