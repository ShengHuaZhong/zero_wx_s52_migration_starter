#pragma once

#include "marine_chart/chart_runtime/feature_portrayal_ir.h"

#include <string>

namespace marine_chart::chart_runtime {

[[nodiscard]] std::string dump_feature_portrayal_ir(const FeaturePortrayalIR& portrayal_ir);

}  // namespace marine_chart::chart_runtime
