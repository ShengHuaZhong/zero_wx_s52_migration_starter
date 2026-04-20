#pragma once

#include "marine_chart/chart_runtime/area_pattern_ir.h"
#include "marine_chart/chart_runtime/display_priority_ir.h"
#include "marine_chart/chart_runtime/line_style_ir.h"
#include "marine_chart/chart_runtime/point_symbol_ir.h"
#include "marine_chart/chart_runtime/text_rule_ir.h"

#include <cstddef>
#include <vector>

namespace marine_chart::chart_runtime {

struct FeaturePortrayalIR final {
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

    bool operator==(const FeaturePortrayalIR&) const noexcept = default;
};

}  // namespace marine_chart::chart_runtime
