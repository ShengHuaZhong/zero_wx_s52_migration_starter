#pragma once

#include "marine_chart/s52_core_headless/lookup_index.h"
#include "marine_chart/s52_core_headless/lookup_key.h"

namespace marine_chart::s52_core_headless {

enum class TextRuleInstructionKind {
    tx,
    te
};

struct TextRuleSelectionEntry final {
    TextRuleInstructionKind kind{TextRuleInstructionKind::tx};
    NeutralString instruction;

    [[nodiscard]] bool empty() const noexcept {
        return instruction.empty();
    }

    bool operator==(const TextRuleSelectionEntry&) const noexcept = default;
};

struct TextRuleSelection final {
    LookupKey lookup_key;
    LookupRawEntry lookup_entry;
    NeutralVector<TextRuleSelectionEntry> entries;

    [[nodiscard]] bool empty() const noexcept {
        return lookup_key.empty() || lookup_entry.empty() || entries.empty();
    }

    bool operator==(const TextRuleSelection&) const noexcept = default;
};

[[nodiscard]] NeutralOptional<TextRuleSelection> select_text_rules(
    const LookupIndex& lookup_index,
    const RuleLayerFeature& feature,
    const MarinerSettings& mariner_settings);

}  // namespace marine_chart::s52_core_headless
