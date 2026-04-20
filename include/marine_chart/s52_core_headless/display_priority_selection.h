#pragma once

#include "marine_chart/s52_core_headless/lookup_index.h"
#include "marine_chart/s52_core_headless/lookup_key.h"

#include <cstdint>

namespace marine_chart::s52_core_headless {

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

[[nodiscard]] DisplayPriorityGroup parse_display_priority_group(NeutralStringView display_priority) noexcept;
[[nodiscard]] int display_priority_sort_rank(DisplayPriorityGroup group) noexcept;

struct DisplayPrioritySelection final {
    LookupKey lookup_key;
    LookupRawEntry lookup_entry;
    DisplayPriorityGroup group{DisplayPriorityGroup::unknown};
    int sort_rank{-1};
    NeutralString source_name;

    [[nodiscard]] bool empty() const noexcept {
        return lookup_key.empty() || lookup_entry.empty() || source_name.empty() || group == DisplayPriorityGroup::unknown
            || sort_rank < 0;
    }

    bool operator==(const DisplayPrioritySelection&) const noexcept = default;
};

[[nodiscard]] NeutralOptional<DisplayPrioritySelection> select_display_priority(
    const LookupIndex& lookup_index,
    const RuleLayerFeature& feature,
    const MarinerSettings& mariner_settings);

}  // namespace marine_chart::s52_core_headless
