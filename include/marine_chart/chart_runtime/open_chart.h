#pragma once

#include "marine_chart/chart_runtime/runtime_render_frame.h"
#include "marine_chart/s52_core_headless/feature_attribute_adapter.h"
#include "marine_chart/s52_core_headless/headless_core_init.h"
#include "marine_chart/s52_core_headless/mariner_settings.h"

#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace marine_chart::chart_runtime {

struct OpenChartResult final {
    RuntimePortrayalBuffer portrayal_buffer;
    RuntimeRenderFrame render_frame;
    std::string palette_name;
    std::size_t feature_count{0};

    [[nodiscard]] bool empty() const noexcept {
        return portrayal_buffer.empty() && render_frame.empty();
    }

    bool operator==(const OpenChartResult&) const noexcept = default;
};

[[nodiscard]] std::optional<OpenChartResult> open_single_chart(
    const s52_core_headless::HeadlessCoreInitialization& initialization,
    const std::vector<s52_core_headless::RuleLayerFeature>& features,
    const s52_core_headless::MarinerSettings& mariner_settings,
    std::string_view palette_name);

}  // namespace marine_chart::chart_runtime
