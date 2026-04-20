#pragma once

#include "marine_chart/chart_runtime/feature_portrayal_ir.h"
#include "marine_chart/s52_core_headless/display_priority_selection.h"

namespace marine_chart::s52_core_headless {

[[nodiscard]] chart_runtime::FeaturePortrayalIR build_feature_portrayal_ir(
    const LookupIndex& lookup_index,
    const RuleLayerFeature& feature,
    const MarinerSettings& mariner_settings);

}  // namespace marine_chart::s52_core_headless
