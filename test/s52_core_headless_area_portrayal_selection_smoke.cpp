#include "marine_chart/s52_core_headless/area_portrayal_selection.h"

int main() {
    const auto lookup_index =
        marine_chart::s52_core_headless::build_lookup_index_from_asset_root("vendor/opencpn_s57data");
    if(!lookup_index.has_value() || lookup_index->empty()) {
        return 1;
    }

    const auto mariner_settings = marine_chart::s52_core_headless::make_default_mariner_settings();

    marine_chart::s52_core_headless::RuleLayerFeature unsare_feature;
    unsare_feature.object_class = "UNSARE";
    unsare_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;
    const auto unsare_selection =
        marine_chart::s52_core_headless::select_area_portrayal(*lookup_index, unsare_feature, mariner_settings);
    if(!unsare_selection.has_value()
        || unsare_selection->fill_color_token != "NODTA"
        || unsare_selection->pattern_name != "NODATA03"
        || unsare_selection->boundary_line_style_name != "SOLD") {
        return 2;
    }

    if(unsare_selection->csp_dispatch.requested()) {
        return 3;
    }

    marine_chart::s52_core_headless::RuleLayerFeature tesare_feature;
    tesare_feature.object_class = "TESARE";
    tesare_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;
    const auto tesare_selection =
        marine_chart::s52_core_headless::select_area_portrayal(*lookup_index, tesare_feature, mariner_settings);
    if(!tesare_selection.has_value()
        || tesare_selection->boundary_line_style_name != "DASH"
        || tesare_selection->csp_dispatch.procedure != marine_chart::s52_core_headless::CspProcedureId::restrn01) {
        return 4;
    }

    marine_chart::s52_core_headless::RuleLayerFeature achare_feature;
    achare_feature.object_class = "ACHARE";
    achare_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;
    if(marine_chart::s52_core_headless::select_area_portrayal(*lookup_index, achare_feature, mariner_settings)
           .has_value()) {
        return 5;
    }

    marine_chart::s52_core_headless::RuleLayerFeature invalid_feature;
    invalid_feature.object_class = "TRFLNE";
    invalid_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::line;
    if(marine_chart::s52_core_headless::select_area_portrayal(*lookup_index, invalid_feature, mariner_settings)
           .has_value()) {
        return 6;
    }

    return 0;
}
