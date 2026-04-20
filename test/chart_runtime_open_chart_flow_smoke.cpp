#include "marine_chart/chart_runtime/open_chart.h"

int main() {
    const auto initialization = marine_chart::s52_core_headless::initialize_headless_core("vendor/opencpn_s57data");
    if(!initialization.has_value() || !initialization->valid()) {
        return 1;
    }

    std::vector<marine_chart::s52_core_headless::RuleLayerFeature> features;

    marine_chart::s52_core_headless::RuleLayerFeature achpnt_feature;
    achpnt_feature.object_class = "ACHPNT";
    achpnt_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::point;
    features.push_back(achpnt_feature);

    marine_chart::s52_core_headless::RuleLayerFeature trflne_feature;
    trflne_feature.object_class = "TRFLNE";
    trflne_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::line;
    features.push_back(trflne_feature);

    marine_chart::s52_core_headless::RuleLayerFeature unsare_feature;
    unsare_feature.object_class = "UNSARE";
    unsare_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;
    features.push_back(unsare_feature);

    marine_chart::s52_core_headless::RuleLayerFeature seaare_feature;
    seaare_feature.object_class = "SEAARE";
    seaare_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;
    features.push_back(seaare_feature);

    const auto result = marine_chart::chart_runtime::open_single_chart(
        *initialization,
        features,
        marine_chart::s52_core_headless::make_default_mariner_settings(),
        "DAY_BRIGHT");
    if(!result.has_value() || result->feature_count != 4 || result->palette_name != "DAY_BRIGHT") {
        return 2;
    }

    if(result->portrayal_buffer.instruction_count() != 8) {
        return 3;
    }

    if(result->portrayal_buffer.point_symbols.empty()) {
        return 52;
    }

    if(result->render_frame.point_commands.empty()) {
        return 42;
    }

    if(result->render_frame.line_commands.empty()) {
        return 43;
    }

    if(result->render_frame.area_commands.empty()) {
        return 44;
    }

    if(result->render_frame.text_commands.empty()) {
        return 45;
    }

    if(result->render_frame.sorted_instructions.size() < 4) {
        return 46;
    }

    if(result->render_frame.command_count() < 4) {
        return 41;
    }

    marine_chart::chart_runtime::OpenChartResult empty_result = *result;
    if(empty_result.empty()) {
        return 5;
    }

    if(marine_chart::chart_runtime::open_single_chart(
           *initialization,
           features,
           marine_chart::s52_core_headless::make_default_mariner_settings(),
           "NOT_A_PALETTE")
           .has_value()) {
        return 6;
    }

    if(marine_chart::chart_runtime::open_single_chart(
           *initialization,
           {},
           marine_chart::s52_core_headless::make_default_mariner_settings(),
           "DAY_BRIGHT")
           .has_value()) {
        return 7;
    }

    return 0;
}
