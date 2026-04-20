#include "marine_chart/s52_core_headless/point_portrayal_selection.h"

namespace marine_chart::s52_core_headless {
namespace {

[[nodiscard]] NeutralOptional<NeutralString> parse_symbol_name(NeutralStringView instruction) {
    const auto symbol_begin = instruction.find("SY(");
    if(symbol_begin == NeutralStringView::npos) {
        return std::nullopt;
    }

    const auto name_begin = symbol_begin + 3;
    const auto name_end = instruction.find_first_of(",)", name_begin);
    if(name_end == NeutralStringView::npos) {
        return std::nullopt;
    }

    const auto symbol_name = make_neutral_string(instruction.substr(name_begin, name_end - name_begin));
    if(symbol_name.empty()) {
        return std::nullopt;
    }

    return symbol_name;
}

}  // namespace

NeutralOptional<PointPortrayalSelection> select_point_portrayal(
    const LookupIndex& lookup_index,
    const RuleLayerFeature& feature,
    const MarinerSettings& mariner_settings) {
    if(feature.primitive_type != FeaturePrimitiveType::point) {
        return std::nullopt;
    }

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

    PointPortrayalSelection selection;
    selection.lookup_key = *lookup_key;
    selection.lookup_entry = bucket->entries.front();
    selection.symbol_name = parse_symbol_name(selection.lookup_entry.instruction).value_or("");
    selection.csp_dispatch = bridge_csp_instruction(selection.lookup_entry.instruction, mariner_settings);

    if(selection.empty()) {
        return std::nullopt;
    }

    return selection;
}

}  // namespace marine_chart::s52_core_headless
