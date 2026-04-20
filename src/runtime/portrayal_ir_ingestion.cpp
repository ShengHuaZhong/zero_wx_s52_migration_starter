#include "marine_chart/chart_runtime/portrayal_ir_ingestion.h"

namespace marine_chart::chart_runtime {

void ingest_feature_portrayal_ir(RuntimePortrayalBuffer& buffer, const FeaturePortrayalIR& portrayal_ir) {
    buffer.point_symbols.insert(
        buffer.point_symbols.end(),
        portrayal_ir.point_symbols.begin(),
        portrayal_ir.point_symbols.end());
    buffer.line_styles.insert(
        buffer.line_styles.end(),
        portrayal_ir.line_styles.begin(),
        portrayal_ir.line_styles.end());
    buffer.area_patterns.insert(
        buffer.area_patterns.end(),
        portrayal_ir.area_patterns.begin(),
        portrayal_ir.area_patterns.end());
    buffer.text_rules.insert(
        buffer.text_rules.end(),
        portrayal_ir.text_rules.begin(),
        portrayal_ir.text_rules.end());
    buffer.display_priorities.insert(
        buffer.display_priorities.end(),
        portrayal_ir.display_priorities.begin(),
        portrayal_ir.display_priorities.end());
}

}  // namespace marine_chart::chart_runtime
