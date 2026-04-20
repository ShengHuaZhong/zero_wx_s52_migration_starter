#include "marine_chart/chart_qt_host/chart_host_widget.h"
#include "marine_chart/chart_runtime/open_chart.h"
#include "marine_chart/s52_core_headless/feature_attribute_adapter.h"
#include "marine_chart/s52_core_headless/headless_core_init.h"
#include "marine_chart/s52_core_headless/mariner_settings.h"

#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDebug>
#include <QString>

#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace {

std::vector<marine_chart::s52_core_headless::RuleLayerFeature> make_demo_chart_features() {
    using marine_chart::s52_core_headless::FeaturePrimitiveType;
    using marine_chart::s52_core_headless::RuleLayerFeature;

    std::vector<RuleLayerFeature> features;

    RuleLayerFeature achpnt_feature;
    achpnt_feature.object_class = "ACHPNT";
    achpnt_feature.primitive_type = FeaturePrimitiveType::point;
    features.push_back(achpnt_feature);

    RuleLayerFeature trflne_feature;
    trflne_feature.object_class = "TRFLNE";
    trflne_feature.primitive_type = FeaturePrimitiveType::line;
    features.push_back(trflne_feature);

    RuleLayerFeature unsare_feature;
    unsare_feature.object_class = "UNSARE";
    unsare_feature.primitive_type = FeaturePrimitiveType::area;
    features.push_back(unsare_feature);

    RuleLayerFeature seaare_feature;
    seaare_feature.object_class = "SEAARE";
    seaare_feature.primitive_type = FeaturePrimitiveType::area;
    features.push_back(seaare_feature);

    return features;
}

std::optional<marine_chart::chart_runtime::OpenChartResult> open_demo_chart(
    std::string_view asset_root,
    std::string_view palette_name) {
    const auto initialization = marine_chart::s52_core_headless::initialize_headless_core(asset_root);
    if(!initialization.has_value() || !initialization->valid()) {
        qCritical() << "Failed to initialize headless core from asset root"
                    << QString::fromStdString(std::string(asset_root));
        return std::nullopt;
    }

    return marine_chart::chart_runtime::open_single_chart(
        *initialization,
        make_demo_chart_features(),
        marine_chart::s52_core_headless::make_default_mariner_settings(),
        palette_name);
}

}  // namespace

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setApplicationName("chart_standalone");

    QCommandLineParser parser;
    parser.setApplicationDescription("Standalone chart host shell");
    parser.addHelpOption();

    const QCommandLineOption smoke_test_option("smoke-test", "Open the built-in chart and exit.");
    const QCommandLineOption asset_root_option(
        "asset-root",
        "Headless asset root to initialize.",
        "path",
        "vendor/opencpn_s57data");
    const QCommandLineOption palette_option(
        "palette",
        "Palette name for the built-in chart.",
        "name",
        "DAY_BRIGHT");

    parser.addOption(smoke_test_option);
    parser.addOption(asset_root_option);
    parser.addOption(palette_option);
    parser.process(app);

    const std::string asset_root = parser.value(asset_root_option).toStdString();
    const std::string palette_name = parser.value(palette_option).toStdString();

    const auto open_chart_result = open_demo_chart(asset_root, palette_name);
    if(!open_chart_result.has_value()) {
        return 1;
    }

    marine_chart::chart_qt_host::ChartHostWidget widget;
    widget.setWindowTitle(QString("chart_standalone - %1 (%2 instructions)")
                              .arg(QString::fromStdString(open_chart_result->palette_name))
                              .arg(open_chart_result->render_frame.sorted_instructions.size()));
    widget.resize(1280, 720);
    widget.set_open_chart_result(*open_chart_result);

    if(parser.isSet(smoke_test_option)) {
        if(!widget.has_chart() || widget.current_command_count() == 0 || widget.current_render_frame() == nullptr) {
            qCritical() << "Standalone host did not retain the opened chart result.";
            return 2;
        }

        return 0;
    }

    widget.show();
    return app.exec();
}
