#pragma once

#include "marine_chart/s52_core_headless/feature_attribute_adapter.h"
#include "marine_chart/s52_core_headless/mariner_settings.h"
#include "marine_chart/s52_core_headless/neutral_containers.h"
#include "marine_chart/s52_core_headless/neutral_string.h"

namespace marine_chart::s52_core_headless {

struct LookupKey final {
    NeutralString object_class;
    NeutralString lookup_type;
    NeutralString table_name;

    [[nodiscard]] bool empty() const noexcept {
        return object_class.empty() || lookup_type.empty() || table_name.empty();
    }

    bool operator==(const LookupKey&) const noexcept = default;
};

[[nodiscard]] NeutralOptional<LookupKey> make_lookup_key(
    const RuleLayerFeature& feature,
    const MarinerSettings& mariner_settings);

}  // namespace marine_chart::s52_core_headless
