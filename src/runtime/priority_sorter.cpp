#include "marine_chart/chart_runtime/priority_sorter.h"

#include <algorithm>
#include <map>
#include <tuple>

namespace marine_chart::chart_runtime {
namespace {

using PriorityKey = std::tuple<PrimitiveKind, std::string, std::string, std::string, std::string>;

struct PriorityValue final {
    DisplayPriorityGroup group{DisplayPriorityGroup::unknown};
    int sort_rank{-1};
    std::string source_name;
};

[[nodiscard]] PriorityKey make_priority_key(const InstructionIR& instruction) {
    return PriorityKey{
        instruction.primitive,
        instruction.source.object_class,
        instruction.source.lookup_type,
        instruction.source.table_name,
        instruction.source.lookup_id};
}

[[nodiscard]] PrioritySortedInstruction make_sorted_instruction(
    const InstructionIR& instruction,
    const PriorityValue& priority_value) {
    PrioritySortedInstruction sorted_instruction;
    sorted_instruction.instruction_id = instruction.stable_id;
    sorted_instruction.instruction_kind = instruction.kind;
    sorted_instruction.primitive = instruction.primitive;
    sorted_instruction.group = priority_value.group;
    sorted_instruction.sort_rank = priority_value.sort_rank;
    sorted_instruction.priority_source_name = priority_value.source_name;
    return sorted_instruction;
}

void append_sorted_instruction(
    std::vector<PrioritySortedInstruction>& sorted_instructions,
    const std::map<PriorityKey, PriorityValue>& priorities,
    const InstructionIR& instruction) {
    if(!instruction.valid() || instruction.kind == InstructionKind::display_priority) {
        return;
    }

    const auto match = priorities.find(make_priority_key(instruction));
    if(match == priorities.end()) {
        return;
    }

    auto sorted_instruction = make_sorted_instruction(instruction, match->second);
    if(sorted_instruction.valid()) {
        sorted_instructions.push_back(std::move(sorted_instruction));
    }
}

template <typename InstructionCollection>
void append_sorted_instructions(
    std::vector<PrioritySortedInstruction>& sorted_instructions,
    const std::map<PriorityKey, PriorityValue>& priorities,
    const InstructionCollection& instructions) {
    for(const auto& instruction_record : instructions) {
        append_sorted_instruction(sorted_instructions, priorities, instruction_record.instruction);
    }
}

}  // namespace

std::vector<PrioritySortedInstruction> sort_render_instructions_by_priority(const RuntimePortrayalBuffer& buffer) {
    std::map<PriorityKey, PriorityValue> priorities;
    for(const auto& display_priority : buffer.display_priorities) {
        if(!display_priority.valid()) {
            continue;
        }

        priorities.try_emplace(
            make_priority_key(display_priority.instruction),
            PriorityValue{
                .group = display_priority.group,
                .sort_rank = display_priority.sort_rank,
                .source_name = display_priority.source_name});
    }

    std::vector<PrioritySortedInstruction> sorted_instructions;
    sorted_instructions.reserve(
        buffer.point_symbols.size() + buffer.line_styles.size() + buffer.area_patterns.size() + buffer.text_rules.size());

    append_sorted_instructions(sorted_instructions, priorities, buffer.point_symbols);
    append_sorted_instructions(sorted_instructions, priorities, buffer.line_styles);
    append_sorted_instructions(sorted_instructions, priorities, buffer.area_patterns);
    append_sorted_instructions(sorted_instructions, priorities, buffer.text_rules);

    std::sort(
        sorted_instructions.begin(),
        sorted_instructions.end(),
        [](const PrioritySortedInstruction& lhs, const PrioritySortedInstruction& rhs) {
            if(lhs.sort_rank != rhs.sort_rank) {
                return lhs.sort_rank < rhs.sort_rank;
            }

            if(lhs.group != rhs.group) {
                return static_cast<int>(lhs.group) < static_cast<int>(rhs.group);
            }

            if(lhs.instruction_kind != rhs.instruction_kind) {
                return static_cast<int>(lhs.instruction_kind) < static_cast<int>(rhs.instruction_kind);
            }

            if(lhs.primitive != rhs.primitive) {
                return static_cast<int>(lhs.primitive) < static_cast<int>(rhs.primitive);
            }

            return lhs.instruction_id < rhs.instruction_id;
        });

    return sorted_instructions;
}

}  // namespace marine_chart::chart_runtime
