#include "marine_chart/s52_core_headless/area_portrayal_selection.h"

namespace marine_chart::s52_core_headless {
namespace {

[[nodiscard]] NeutralOptional<NeutralString> parse_instruction_name(
    NeutralStringView instruction,
    NeutralStringView marker) {
    const auto token_begin = instruction.find(marker);
    if(token_begin == NeutralStringView::npos) {
        return std::nullopt;
    }

    const auto name_begin = token_begin + marker.size();
    const auto name_end = instruction.find_first_of(",)", name_begin);
    if(name_end == NeutralStringView::npos) {
        return std::nullopt;
    }

    const auto token_name = make_neutral_string(instruction.substr(name_begin, name_end - name_begin));
    if(token_name.empty()) {
        return std::nullopt;
    }

    return token_name;
}

}  // namespace

NeutralOptional<AreaPortrayalSelection> select_area_portrayal(
    const LookupIndex& lookup_index,
    const RuleLayerFeature& feature,
    const MarinerSettings& mariner_settings) {
    if(feature.primitive_type != FeaturePrimitiveType::area) {
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

    AreaPortrayalSelection selection;
    selection.lookup_key = *lookup_key;
    selection.lookup_entry = bucket->entries.front();
    selection.fill_color_token = parse_instruction_name(selection.lookup_entry.instruction, "AC(").value_or("");
    selection.pattern_name = parse_instruction_name(selection.lookup_entry.instruction, "AP(").value_or("");
    selection.boundary_line_style_name =
        parse_instruction_name(selection.lookup_entry.instruction, "LS(").value_or("");
    selection.csp_dispatch = bridge_csp_instruction(selection.lookup_entry.instruction, mariner_settings);

    if(selection.empty()) {
        return std::nullopt;
    }

    return selection;
}

}  // namespace marine_chart::s52_core_headless
