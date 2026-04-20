#pragma once

#include "marine_chart/s52_core_headless/csp_minimal_bridge.h"
#include "marine_chart/s52_core_headless/lookup_index.h"
#include "marine_chart/s52_core_headless/lookup_key.h"

namespace marine_chart::s52_core_headless {

struct AreaPortrayalSelection final {
    LookupKey lookup_key;
    LookupRawEntry lookup_entry;
    NeutralString fill_color_token;
    NeutralString pattern_name;
    NeutralString boundary_line_style_name;
    CspDispatchRequest csp_dispatch;

    [[nodiscard]] bool empty() const noexcept {
        return lookup_key.empty()
            || lookup_entry.empty()
            || (fill_color_token.empty()
                && pattern_name.empty()
                && boundary_line_style_name.empty()
                && !csp_dispatch.requested());
    }

    bool operator==(const AreaPortrayalSelection&) const noexcept = default;
};

[[nodiscard]] NeutralOptional<AreaPortrayalSelection> select_area_portrayal(
    const LookupIndex& lookup_index,
    const RuleLayerFeature& feature,
    const MarinerSettings& mariner_settings);

}  // namespace marine_chart::s52_core_headless
