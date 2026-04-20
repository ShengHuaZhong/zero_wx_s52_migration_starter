#pragma once

#include "marine_chart/chart_runtime/instruction_ir.h"

#include <cstdint>
#include <string>

namespace marine_chart::chart_runtime {

enum class DisplayPriorityGroup : std::uint8_t {
    unknown,
    no_data,
    group_1,
    area_1,
    area_2,
    point_symbol,
    line_symbol,
    area_symbol,
    routing,
    hazards,
    mariners
};

struct DisplayPriorityIR final {
    InstructionIR instruction;
    DisplayPriorityGroup group{DisplayPriorityGroup::unknown};
    int sort_rank{-1};
    std::string source_name;

    [[nodiscard]] bool valid() const noexcept {
        return instruction.valid() && instruction.kind == InstructionKind::display_priority
            && instruction.primitive != PrimitiveKind::unknown && group != DisplayPriorityGroup::unknown
            && sort_rank >= 0 && !source_name.empty();
    }

    bool operator==(const DisplayPriorityIR&) const noexcept = default;
};

}  // namespace marine_chart::chart_runtime
