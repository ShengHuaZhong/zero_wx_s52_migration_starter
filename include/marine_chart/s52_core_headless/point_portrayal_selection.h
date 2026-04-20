#pragma once

#include "marine_chart/s52_core_headless/csp_minimal_bridge.h"
#include "marine_chart/s52_core_headless/lookup_index.h"
#include "marine_chart/s52_core_headless/lookup_key.h"

namespace marine_chart::s52_core_headless {

struct PointPortrayalSelection final {
    LookupKey lookup_key;
    LookupRawEntry lookup_entry;
    NeutralString symbol_name;
    CspDispatchRequest csp_dispatch;

    [[nodiscard]] bool empty() const noexcept {
        return lookup_key.empty()
            || lookup_entry.empty()
            || (symbol_name.empty() && !csp_dispatch.requested());
    }

    bool operator==(const PointPortrayalSelection&) const noexcept = default;
};

[[nodiscard]] NeutralOptional<PointPortrayalSelection> select_point_portrayal(
    const LookupIndex& lookup_index,
    const RuleLayerFeature& feature,
    const MarinerSettings& mariner_settings);

}  // namespace marine_chart::s52_core_headless
