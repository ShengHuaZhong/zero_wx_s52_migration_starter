#include "marine_chart/s52_core_headless/line_portrayal_selection.h"

int main() {
    const auto lookup_index =
        marine_chart::s52_core_headless::build_lookup_index_from_asset_root("vendor/opencpn_s57data");
    if(!lookup_index.has_value() || lookup_index->empty()) {
        return 1;
    }

    const auto mariner_settings = marine_chart::s52_core_headless::make_default_mariner_settings();

    marine_chart::s52_core_headless::RuleLayerFeature trflne_feature;
    trflne_feature.object_class = "TRFLNE";
    trflne_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::line;
    const auto trflne_selection =
        marine_chart::s52_core_headless::select_line_portrayal(*lookup_index, trflne_feature, mariner_settings);
    if(!trflne_selection.has_value() || trflne_selection->line_style_name != "DASH") {
        return 2;
    }

    if(trflne_selection->csp_dispatch.requested()) {
        return 3;
    }

    marine_chart::s52_core_headless::RuleLayerFeature depare_feature;
    depare_feature.object_class = "DEPARE";
    depare_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::line;
    const auto depare_selection =
        marine_chart::s52_core_headless::select_line_portrayal(*lookup_index, depare_feature, mariner_settings);
    if(!depare_selection.has_value()
        || depare_selection->csp_dispatch.procedure != marine_chart::s52_core_headless::CspProcedureId::depcnt02) {
        return 4;
    }

    if(!depare_selection->line_style_name.empty()) {
        return 5;
    }

    marine_chart::s52_core_headless::RuleLayerFeature invalid_feature;
    invalid_feature.object_class = "ACHPNT";
    invalid_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::point;
    if(marine_chart::s52_core_headless::select_line_portrayal(*lookup_index, invalid_feature, mariner_settings)
           .has_value()) {
        return 6;
    }

    return 0;
}
