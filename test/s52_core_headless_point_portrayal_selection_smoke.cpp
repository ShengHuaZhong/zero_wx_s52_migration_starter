#include "marine_chart/s52_core_headless/point_portrayal_selection.h"

int main() {
    const auto lookup_index =
        marine_chart::s52_core_headless::build_lookup_index_from_asset_root("vendor/opencpn_s57data");
    if(!lookup_index.has_value() || lookup_index->empty()) {
        return 1;
    }

    marine_chart::s52_core_headless::RuleLayerFeature achpnt_feature;
    achpnt_feature.object_class = "ACHPNT";
    achpnt_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::point;

    auto mariner_settings = marine_chart::s52_core_headless::make_default_mariner_settings();
    const auto achpnt_selection =
        marine_chart::s52_core_headless::select_point_portrayal(*lookup_index, achpnt_feature, mariner_settings);
    if(!achpnt_selection.has_value() || achpnt_selection->symbol_name != "ACHPNT01") {
        return 2;
    }

    if(achpnt_selection->csp_dispatch.requested()) {
        return 3;
    }

    marine_chart::s52_core_headless::RuleLayerFeature marcul_feature;
    marcul_feature.object_class = "MARCUL";
    marcul_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::point;
    mariner_settings.point_symbol_style = marine_chart::s52_core_headless::PointSymbolStyle::paper_chart;

    const auto marcul_selection =
        marine_chart::s52_core_headless::select_point_portrayal(*lookup_index, marcul_feature, mariner_settings);
    if(!marcul_selection.has_value() || marcul_selection->symbol_name != "MARCUL02") {
        return 4;
    }

    marine_chart::s52_core_headless::RuleLayerFeature lights_feature;
    lights_feature.object_class = "LIGHTS";
    lights_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::point;
    if(marine_chart::s52_core_headless::select_point_portrayal(*lookup_index, lights_feature, mariner_settings)
           .has_value()) {
        return 5;
    }

    marine_chart::s52_core_headless::RuleLayerFeature invalid_feature;
    invalid_feature.object_class = "ACHARE";
    invalid_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;
    if(marine_chart::s52_core_headless::select_point_portrayal(*lookup_index, invalid_feature, mariner_settings)
           .has_value()) {
        return 6;
    }

    return 0;
}
