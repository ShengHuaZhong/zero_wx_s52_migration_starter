#pragma once

#include "marine_chart/chart_runtime/portrayal_ir_ingestion.h"

#include <string>
#include <vector>

namespace marine_chart::chart_runtime {

struct PrioritySortedInstruction final {
    std::string instruction_id;
    InstructionKind instruction_kind{InstructionKind::unknown};
    PrimitiveKind primitive{PrimitiveKind::unknown};
    DisplayPriorityGroup group{DisplayPriorityGroup::unknown};
    int sort_rank{-1};
    std::string priority_source_name;

    [[nodiscard]] bool valid() const noexcept {
        return !instruction_id.empty() && instruction_kind != InstructionKind::unknown
            && instruction_kind != InstructionKind::display_priority && primitive != PrimitiveKind::unknown
            && group != DisplayPriorityGroup::unknown && sort_rank >= 0 && !priority_source_name.empty();
    }

    bool operator==(const PrioritySortedInstruction&) const noexcept = default;
};

[[nodiscard]] std::vector<PrioritySortedInstruction> sort_render_instructions_by_priority(
    const RuntimePortrayalBuffer& buffer);

}  // namespace marine_chart::chart_runtime
