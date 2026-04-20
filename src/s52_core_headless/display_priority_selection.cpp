#include "marine_chart/s52_core_headless/display_priority_selection.h"

namespace marine_chart::s52_core_headless {

DisplayPriorityGroup parse_display_priority_group(NeutralStringView display_priority) noexcept {
    if(display_priority == "No data") {
        return DisplayPriorityGroup::no_data;
    }

    if(display_priority == "Group 1") {
        return DisplayPriorityGroup::group_1;
    }

    if(display_priority == "Area 1") {
        return DisplayPriorityGroup::area_1;
    }

    if(display_priority == "Area 2") {
        return DisplayPriorityGroup::area_2;
    }

    if(display_priority == "Point Symbol") {
        return DisplayPriorityGroup::point_symbol;
    }

    if(display_priority == "Line Symbol") {
        return DisplayPriorityGroup::line_symbol;
    }

    if(display_priority == "Area Symbol") {
        return DisplayPriorityGroup::area_symbol;
    }

    if(display_priority == "Routing") {
        return DisplayPriorityGroup::routing;
    }

    if(display_priority == "Hazards") {
        return DisplayPriorityGroup::hazards;
    }

    if(display_priority == "Mariners") {
        return DisplayPriorityGroup::mariners;
    }

    return DisplayPriorityGroup::unknown;
}

int display_priority_sort_rank(DisplayPriorityGroup group) noexcept {
    switch(group) {
    case DisplayPriorityGroup::no_data:
        return 0;
    case DisplayPriorityGroup::group_1:
        return 1;
    case DisplayPriorityGroup::area_1:
        return 2;
    case DisplayPriorityGroup::area_2:
        return 3;
    case DisplayPriorityGroup::point_symbol:
        return 4;
    case DisplayPriorityGroup::line_symbol:
        return 5;
    case DisplayPriorityGroup::area_symbol:
        return 6;
    case DisplayPriorityGroup::routing:
        return 7;
    case DisplayPriorityGroup::hazards:
        return 8;
    case DisplayPriorityGroup::mariners:
        return 9;
    case DisplayPriorityGroup::unknown:
    default:
        return -1;
    }
}

NeutralOptional<DisplayPrioritySelection> select_display_priority(
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

    DisplayPrioritySelection selection;
    selection.lookup_key = *lookup_key;
    selection.lookup_entry = bucket->entries.front();
    selection.source_name = selection.lookup_entry.display_priority;
    selection.group = parse_display_priority_group(selection.source_name);
    selection.sort_rank = display_priority_sort_rank(selection.group);

    if(selection.empty()) {
        return std::nullopt;
    }

    return selection;
}

}  // namespace marine_chart::s52_core_headless
