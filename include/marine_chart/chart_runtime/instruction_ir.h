#pragma once

#include <string>

namespace marine_chart::chart_runtime {

enum class InstructionKind {
    unknown,
    point_symbol,
    line_style,
    area_pattern,
    text_rule,
    display_priority
};

enum class PrimitiveKind {
    unknown,
    point,
    line,
    area
};

struct InstructionSource final {
    std::string object_class;
    std::string lookup_type;
    std::string table_name;
    std::string lookup_id;
    std::string raw_instruction;

    [[nodiscard]] bool empty() const noexcept {
        return object_class.empty() || lookup_type.empty() || table_name.empty() || lookup_id.empty();
    }

    bool operator==(const InstructionSource&) const noexcept = default;
};

struct InstructionIR final {
    InstructionKind kind{InstructionKind::unknown};
    PrimitiveKind primitive{PrimitiveKind::unknown};
    std::string stable_id;
    InstructionSource source;

    [[nodiscard]] bool valid() const noexcept {
        return kind != InstructionKind::unknown && primitive != PrimitiveKind::unknown && !stable_id.empty()
            && !source.empty();
    }

    bool operator==(const InstructionIR&) const noexcept = default;
};

}  // namespace marine_chart::chart_runtime
