#pragma once

#include "marine_chart/s52_core_headless/feature_attribute_adapter.h"

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace marine_chart::chart_runtime {

struct S57DatasetLoadResult final {
    std::vector<s52_core_headless::RuleLayerFeature> features;
    std::size_t source_file_count{0};
    std::size_t frid_record_count{0};

    [[nodiscard]] bool valid() const noexcept {
        return source_file_count > 0 && !features.empty() && frid_record_count >= features.size();
    }
};

[[nodiscard]] std::optional<S57DatasetLoadResult> load_rule_layer_features_from_s57_dataset(
    std::string_view dataset_root,
    std::string_view asset_root);

}  // namespace marine_chart::chart_runtime
