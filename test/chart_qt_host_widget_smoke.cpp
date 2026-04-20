#include "marine_chart/chart_qt_host/chart_host_widget.h"

#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

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

    const auto open_chart_result = marine_chart::chart_runtime::open_single_chart(
        *initialization,
        features,
        marine_chart::s52_core_headless::make_default_mariner_settings(),
        "DAY_BRIGHT");
    if(!open_chart_result.has_value()) {
        return 2;
    }

    marine_chart::chart_qt_host::ChartHostWidget widget;
    if(widget.has_chart() || widget.current_command_count() != 0 || widget.current_render_frame() != nullptr) {
        return 3;
    }

    widget.set_open_chart_result(*open_chart_result);
    if(!widget.has_chart() || widget.current_command_count() < 4 || widget.current_render_frame() == nullptr
        || widget.current_render_frame()->sorted_instructions.size() < 4) {
        return 4;
    }

    widget.clear_chart();
    if(widget.has_chart() || widget.current_command_count() != 0 || widget.current_render_frame() != nullptr) {
        return 5;
    }

    return 0;
}
