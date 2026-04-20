#include "marine_chart/chart_qt_host/chart_host_widget.h"
#include "marine_chart/chart_runtime/open_chart.h"
#include "marine_chart/chart_runtime/s57_dataset_ingestion.h"
#include "marine_chart/s52_core_headless/feature_attribute_adapter.h"
#include "marine_chart/s52_core_headless/headless_core_init.h"
#include "marine_chart/s52_core_headless/mariner_settings.h"

#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDebug>
#include <QElapsedTimer>
#include <QEventLoop>
#include <QImage>
#include <QString>

#include <filesystem>
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

std::optional<marine_chart::chart_runtime::OpenChartResult> open_real_s57_chart(
    std::string_view asset_root,
    std::string_view palette_name,
    std::string_view s57_dataset_root) {
    const auto initialization = marine_chart::s52_core_headless::initialize_headless_core(asset_root);
    if(!initialization.has_value() || !initialization->valid()) {
        qCritical() << "Failed to initialize headless core from asset root"
                    << QString::fromStdString(std::string(asset_root));
        return std::nullopt;
    }

    const auto loaded_dataset = marine_chart::chart_runtime::load_rule_layer_features_from_s57_dataset(
        s57_dataset_root,
        asset_root);
    if(!loaded_dataset.has_value() || !loaded_dataset->valid()) {
        qCritical() << "Failed to extract S57 features from dataset root"
                    << QString::fromStdString(std::string(s57_dataset_root));
        return std::nullopt;
    }

    return marine_chart::chart_runtime::open_single_chart(
        *initialization,
        loaded_dataset->features,
        marine_chart::s52_core_headless::make_default_mariner_settings(),
        palette_name);
}

void drain_render_events(
    QApplication& app,
    marine_chart::chart_qt_host::ChartHostWidget& widget,
    int timeout_ms = 500) {
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed() < timeout_ms) {
        widget.update();
        app.processEvents(QEventLoop::AllEvents, 50);
    }
}

}  // namespace

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setApplicationName("chart_standalone");

    QCommandLineParser parser;
    parser.setApplicationDescription("Standalone chart host shell");
    parser.addHelpOption();

    const QCommandLineOption smoke_test_option("smoke-test", "Open the built-in chart and exit.");
    const QCommandLineOption non_blank_smoke_option(
        "non-blank-smoke",
        "Render the built-in chart offscreen and verify the framebuffer is not blank.");
    const QCommandLineOption real_s57_smoke_option(
        "real-s57-smoke",
        "Open a real external S57 dataset through the host smoke path and exit.");
    const QCommandLineOption asset_root_option(
        "asset-root",
        "Headless asset root to initialize.",
        "path",
        "vendor/opencpn_s57data");
    const QCommandLineOption s57_root_option(
        "s57-root",
        "External S57 dataset root used by --real-s57-smoke.",
        "path",
        qEnvironmentVariable("S57_TESTDATA_ROOT"));
    const QCommandLineOption palette_option(
        "palette",
        "Palette name for the built-in chart.",
        "name",
        "DAY_BRIGHT");

    parser.addOption(smoke_test_option);
    parser.addOption(non_blank_smoke_option);
    parser.addOption(real_s57_smoke_option);
    parser.addOption(asset_root_option);
    parser.addOption(s57_root_option);
    parser.addOption(palette_option);
    parser.process(app);

    const std::string asset_root = parser.value(asset_root_option).toStdString();
    const std::string s57_root = parser.value(s57_root_option).toStdString();
    const std::string palette_name = parser.value(palette_option).toStdString();

    std::optional<marine_chart::chart_runtime::OpenChartResult> open_chart_result;
    if(parser.isSet(real_s57_smoke_option)) {
        if(s57_root.empty()) {
            qInfo() << "Skipping real S57 smoke because S57 dataset root is empty.";
            return 125;
        }

        if(!std::filesystem::exists(s57_root) || !std::filesystem::is_directory(s57_root)) {
            qInfo() << "Skipping real S57 smoke because dataset root is unavailable:"
                    << QString::fromStdString(s57_root);
            return 125;
        }

        open_chart_result = open_real_s57_chart(asset_root, palette_name, s57_root);
    } else {
        open_chart_result = open_demo_chart(asset_root, palette_name);
    }

    if(!open_chart_result.has_value()) {
        return parser.isSet(real_s57_smoke_option) ? 4 : 1;
    }

    marine_chart::chart_qt_host::ChartHostWidget widget;
    widget.setWindowTitle(QString("chart_standalone - %1 (%2 instructions)")
                              .arg(QString::fromStdString(open_chart_result->palette_name))
                              .arg(open_chart_result->render_frame.sorted_instructions.size()));
    widget.resize(1280, 720);

    if(parser.isSet(smoke_test_option)) {
        widget.set_open_chart_result(*open_chart_result);
        if(!widget.has_chart() || widget.current_command_count() == 0 || widget.current_render_frame() == nullptr) {
            qCritical() << "Standalone host did not retain the opened chart result.";
            return 2;
        }

        return 0;
    }

    if(parser.isSet(real_s57_smoke_option)) {
        widget.set_open_chart_result(*open_chart_result);
        if(!widget.has_chart() || widget.current_command_count() == 0 || widget.current_render_frame() == nullptr) {
            qCritical() << "Real S57 smoke did not produce a usable host render frame.";
            return 5;
        }

        return 0;
    }

    if(parser.isSet(non_blank_smoke_option)) {
        widget.show();
        drain_render_events(app, widget);
        const QImage empty_framebuffer = widget.grabFramebuffer();

        widget.set_open_chart_result(*open_chart_result);
        drain_render_events(app, widget);
        const QImage chart_framebuffer = widget.grabFramebuffer();

        if(empty_framebuffer.isNull() || chart_framebuffer.isNull() || empty_framebuffer == chart_framebuffer) {
            qCritical() << "Standalone host framebuffer stayed blank after opening the chart.";
            return 3;
        }

        return 0;
    }

    widget.set_open_chart_result(*open_chart_result);
    widget.show();
    return app.exec();
}
