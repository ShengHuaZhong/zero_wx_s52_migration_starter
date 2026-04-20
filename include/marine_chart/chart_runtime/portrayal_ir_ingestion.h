#pragma once

#include "marine_chart/chart_runtime/feature_portrayal_ir.h"

namespace marine_chart::chart_runtime {

struct RuntimePortrayalBuffer final {
    std::vector<PointSymbolIR> point_symbols;
    std::vector<LineStyleIR> line_styles;
    std::vector<AreaPatternIR> area_patterns;
    std::vector<TextRuleIR> text_rules;
    std::vector<DisplayPriorityIR> display_priorities;

    [[nodiscard]] bool empty() const noexcept {
        return point_symbols.empty() && line_styles.empty() && area_patterns.empty() && text_rules.empty()
            && display_priorities.empty();
    }

    [[nodiscard]] std::size_t instruction_count() const noexcept {
        return point_symbols.size() + line_styles.size() + area_patterns.size() + text_rules.size()
            + display_priorities.size();
    }

    bool operator==(const RuntimePortrayalBuffer&) const noexcept = default;
};

void ingest_feature_portrayal_ir(RuntimePortrayalBuffer& buffer, const FeaturePortrayalIR& portrayal_ir);

}  // namespace marine_chart::chart_runtime
