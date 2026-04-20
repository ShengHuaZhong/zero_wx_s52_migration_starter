#include "marine_chart/s52_core_headless/display_priority_selection.h"

int main() {
    const auto lookup_index =
        marine_chart::s52_core_headless::build_lookup_index_from_asset_root("vendor/opencpn_s57data");
    if(!lookup_index.has_value() || lookup_index->empty()) {
        return 1;
    }

    const auto mariner_settings = marine_chart::s52_core_headless::make_default_mariner_settings();

    marine_chart::s52_core_headless::RuleLayerFeature seaare_feature;
    seaare_feature.object_class = "SEAARE";
    seaare_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;
    const auto seaare_selection =
        marine_chart::s52_core_headless::select_display_priority(*lookup_index, seaare_feature, mariner_settings);
    if(!seaare_selection.has_value()
        || seaare_selection->group != marine_chart::s52_core_headless::DisplayPriorityGroup::area_2
        || seaare_selection->sort_rank != 3
        || seaare_selection->source_name != "Area 2") {
        return 2;
    }

    marine_chart::s52_core_headless::RuleLayerFeature achpnt_feature;
    achpnt_feature.object_class = "ACHPNT";
    achpnt_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::point;
    const auto achpnt_selection =
        marine_chart::s52_core_headless::select_display_priority(*lookup_index, achpnt_feature, mariner_settings);
    if(!achpnt_selection.has_value()
        || achpnt_selection->group != marine_chart::s52_core_headless::DisplayPriorityGroup::hazards
        || achpnt_selection->sort_rank != 8
        || achpnt_selection->source_name != "Hazards") {
        return 3;
    }

    marine_chart::s52_core_headless::RuleLayerFeature trflne_feature;
    trflne_feature.object_class = "TRFLNE";
    trflne_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::line;
    const auto trflne_selection =
        marine_chart::s52_core_headless::select_display_priority(*lookup_index, trflne_feature, mariner_settings);
    if(!trflne_selection.has_value()
        || trflne_selection->group != marine_chart::s52_core_headless::DisplayPriorityGroup::area_symbol
        || trflne_selection->sort_rank != 6
        || trflne_selection->source_name != "Area Symbol") {
        return 4;
    }

    marine_chart::s52_core_headless::RuleLayerFeature mcovr_feature;
    mcovr_feature.object_class = "M_COVR";
    mcovr_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;
    const auto mcovr_selection =
        marine_chart::s52_core_headless::select_display_priority(*lookup_index, mcovr_feature, mariner_settings);
    if(!mcovr_selection.has_value()
        || mcovr_selection->group != marine_chart::s52_core_headless::DisplayPriorityGroup::group_1
        || mcovr_selection->sort_rank != 1
        || mcovr_selection->source_name != "Group 1") {
        return 5;
    }

    marine_chart::s52_core_headless::RuleLayerFeature lndare_feature;
    lndare_feature.object_class = "LNDARE";
    lndare_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;
    if(marine_chart::s52_core_headless::select_display_priority(*lookup_index, lndare_feature, mariner_settings)
           .has_value()) {
        return 6;
    }

    marine_chart::s52_core_headless::RuleLayerFeature invalid_feature;
    invalid_feature.object_class = "UNKNOWN";
    invalid_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::point;
    if(marine_chart::s52_core_headless::select_display_priority(*lookup_index, invalid_feature, mariner_settings)
           .has_value()) {
        return 7;
    }

    return 0;
}
