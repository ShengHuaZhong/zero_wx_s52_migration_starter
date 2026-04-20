#include "marine_chart/chart_runtime/open_chart.h"

#include "marine_chart/s52_core_headless/lookup_index.h"
#include "marine_chart/s52_core_headless/portrayal_ir_pipeline.h"

namespace marine_chart::chart_runtime {
namespace {

[[nodiscard]] std::optional<RuntimePaletteColors> load_runtime_palette_colors(
    const s52_core_headless::AssetCatalogs& asset_catalogs,
    std::string_view palette_name) {
    if(asset_catalogs.palettes.empty() || palette_name.empty()) {
        return std::nullopt;
    }

    const auto palette_match = asset_catalogs.palettes.palettes.find(std::string{palette_name});
    if(palette_match == asset_catalogs.palettes.palettes.end()) {
        return std::nullopt;
    }

    RuntimePaletteColors palette_colors;
    palette_colors.palette_name = std::string{palette_name};
    palette_colors.graphics_file_name = palette_match->second.graphics_file_name;

    for(const auto& [color_token, color] : palette_match->second.entries) {
        palette_colors.entries.emplace(
            color_token,
            make_runtime_color(color.red, color.green, color.blue, color.alpha));
    }

    if(palette_colors.empty()) {
        return std::nullopt;
    }

    return palette_colors;
}

}  // namespace

std::optional<OpenChartResult> open_single_chart(
    const s52_core_headless::HeadlessCoreInitialization& initialization,
    const std::vector<s52_core_headless::RuleLayerFeature>& features,
    const s52_core_headless::MarinerSettings& mariner_settings,
    std::string_view palette_name) {
    if(!initialization.valid() || features.empty() || !mariner_settings.valid() || palette_name.empty()) {
        return std::nullopt;
    }

    const auto lookup_index = s52_core_headless::build_lookup_index_from_asset_root(initialization.asset_root);
    const auto palette_colors = load_runtime_palette_colors(initialization.asset_catalogs, palette_name);
    if(!lookup_index.has_value() || !palette_colors.has_value()) {
        return std::nullopt;
    }

    OpenChartResult result;
    result.palette_name = std::string{palette_name};
    result.feature_count = features.size();

    for(const auto& feature : features) {
        if(feature.empty()) {
            continue;
        }

        const auto feature_portrayal_ir =
            s52_core_headless::build_feature_portrayal_ir(*lookup_index, feature, mariner_settings);
        ingest_feature_portrayal_ir(result.portrayal_buffer, feature_portrayal_ir);
    }

    result.render_frame =
        build_runtime_render_frame(result.portrayal_buffer, initialization.asset_catalogs, *palette_colors);
    return result;
}

}  // namespace marine_chart::chart_runtime
