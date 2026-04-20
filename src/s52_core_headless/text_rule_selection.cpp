#include "marine_chart/s52_core_headless/text_rule_selection.h"

namespace marine_chart::s52_core_headless {
namespace {

[[nodiscard]] NeutralStringView trim_ascii_whitespace(NeutralStringView text) {
    std::size_t begin = 0;
    while(begin < text.size() && (text[begin] == ' ' || text[begin] == '\t' || text[begin] == '\r' || text[begin] == '\n')) {
        ++begin;
    }

    std::size_t end = text.size();
    while(end > begin
        && (text[end - 1] == ' ' || text[end - 1] == '\t' || text[end - 1] == '\r' || text[end - 1] == '\n')) {
        --end;
    }

    return text.substr(begin, end - begin);
}

[[nodiscard]] NeutralVector<NeutralStringView> split_top_level_instruction_clauses(NeutralStringView instruction) {
    NeutralVector<NeutralStringView> clauses;

    std::size_t clause_begin = 0;
    int paren_depth = 0;
    for(std::size_t index = 0; index < instruction.size(); ++index) {
        const auto ch = instruction[index];
        if(ch == '(') {
            ++paren_depth;
            continue;
        }

        if(ch == ')') {
            if(paren_depth > 0) {
                --paren_depth;
            }
            continue;
        }

        if(ch == ';' && paren_depth == 0) {
            clauses.push_back(trim_ascii_whitespace(instruction.substr(clause_begin, index - clause_begin)));
            clause_begin = index + 1;
        }
    }

    const auto tail = trim_ascii_whitespace(instruction.substr(clause_begin));
    if(!tail.empty()) {
        clauses.push_back(tail);
    }

    return clauses;
}

[[nodiscard]] NeutralOptional<TextRuleSelectionEntry> make_text_rule_selection_entry(NeutralStringView clause) {
    if(clause.starts_with("TX(")) {
        return TextRuleSelectionEntry{TextRuleInstructionKind::tx, make_neutral_string(clause)};
    }

    if(clause.starts_with("TE(")) {
        return TextRuleSelectionEntry{TextRuleInstructionKind::te, make_neutral_string(clause)};
    }

    return std::nullopt;
}

}  // namespace

NeutralOptional<TextRuleSelection> select_text_rules(
    const LookupIndex& lookup_index,
    const RuleLayerFeature& feature,
    const MarinerSettings& mariner_settings) {
    const auto lookup_key = make_lookup_key(feature, mariner_settings);
    if(!lookup_key.has_value()) {
        return std::nullopt;
    }

    const auto* bucket = find_lookup_index_bucket(
        lookup_index,
        lookup_key->object_class,
        lookup_key->lookup_type,
        lookup_key->table_name);
    if(bucket == nullptr || bucket->entries.size() != 1) {
        return std::nullopt;
    }

    TextRuleSelection selection;
    selection.lookup_key = *lookup_key;
    selection.lookup_entry = bucket->entries.front();

    for(const auto clause : split_top_level_instruction_clauses(selection.lookup_entry.instruction)) {
        const auto entry = make_text_rule_selection_entry(clause);
        if(entry.has_value()) {
            selection.entries.push_back(*entry);
        }
    }

    if(selection.empty()) {
        return std::nullopt;
    }

    return selection;
}

}  // namespace marine_chart::s52_core_headless
