#include "marine_chart/s52_core_headless/text_rule_selection.h"

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
        marine_chart::s52_core_headless::select_text_rules(*lookup_index, seaare_feature, mariner_settings);
    if(!seaare_selection.has_value()
        || seaare_selection->entries.size() != 1
        || seaare_selection->entries.front().kind != marine_chart::s52_core_headless::TextRuleInstructionKind::tx
        || seaare_selection->entries.front().instruction != "TX(OBJNAM,1,2,3,'15110',0,0,CHBLK,26)") {
        return 2;
    }

    marine_chart::s52_core_headless::RuleLayerFeature achbrt_feature;
    achbrt_feature.object_class = "ACHBRT";
    achbrt_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::point;
    const auto achbrt_selection =
        marine_chart::s52_core_headless::select_text_rules(*lookup_index, achbrt_feature, mariner_settings);
    if(!achbrt_selection.has_value()
        || achbrt_selection->entries.size() != 1
        || achbrt_selection->entries.front().kind != marine_chart::s52_core_headless::TextRuleInstructionKind::te
        || achbrt_selection->entries.front().instruction != "TE('%s','OBJNAM',3,1,2,'15110',1,0,CHBLK,29)") {
        return 3;
    }

    marine_chart::s52_core_headless::RuleLayerFeature lndare_feature;
    lndare_feature.object_class = "LNDARE";
    lndare_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::point;
    if(marine_chart::s52_core_headless::select_text_rules(*lookup_index, lndare_feature, mariner_settings)
           .has_value()) {
        return 4;
    }

    marine_chart::s52_core_headless::RuleLayerFeature bridge_feature;
    bridge_feature.object_class = "BRIDGE";
    bridge_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;
    if(marine_chart::s52_core_headless::select_text_rules(*lookup_index, bridge_feature, mariner_settings)
           .has_value()) {
        return 5;
    }

    marine_chart::s52_core_headless::RuleLayerFeature trflne_feature;
    trflne_feature.object_class = "TRFLNE";
    trflne_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::line;
    if(marine_chart::s52_core_headless::select_text_rules(*lookup_index, trflne_feature, mariner_settings)
           .has_value()) {
        return 6;
    }

    return 0;
}
