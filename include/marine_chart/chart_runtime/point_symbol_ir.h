#pragma once

#include "marine_chart/chart_runtime/instruction_ir.h"

#include <string>

namespace marine_chart::chart_runtime {

struct PointSymbolIR final {
    InstructionIR instruction;
    std::string symbol_name;

    [[nodiscard]] bool valid() const noexcept {
        return instruction.valid() && instruction.kind == InstructionKind::point_symbol && !symbol_name.empty();
    }

    bool operator==(const PointSymbolIR&) const noexcept = default;
};

}  // namespace marine_chart::chart_runtime
