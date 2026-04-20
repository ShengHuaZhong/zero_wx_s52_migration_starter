#include "marine_chart/s52_core_headless/portrayal_ir_pipeline.h"

int main() {
    const auto lookup_index =
        marine_chart::s52_core_headless::build_lookup_index_from_asset_root("vendor/opencpn_s57data");
    if(!lookup_index.has_value() || lookup_index->empty()) {
        return 1;
    }

    const auto mariner_settings = marine_chart::s52_core_headless::make_default_mariner_settings();

    marine_chart::s52_core_headless::RuleLayerFeature achpnt_feature;
    achpnt_feature.object_class = "ACHPNT";
    achpnt_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::point;
    const auto achpnt_ir =
        marine_chart::s52_core_headless::build_feature_portrayal_ir(*lookup_index, achpnt_feature, mariner_settings);
    if(achpnt_ir.point_symbols.size() != 1
        || achpnt_ir.point_symbols.front().symbol_name != "ACHPNT01"
        || achpnt_ir.display_priorities.size() != 1
        || achpnt_ir.display_priorities.front().source_name != "Hazards"
        || achpnt_ir.instruction_count() != 2) {
        return 2;
    }

    marine_chart::s52_core_headless::RuleLayerFeature trflne_feature;
    trflne_feature.object_class = "TRFLNE";
    trflne_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::line;
    const auto trflne_ir =
        marine_chart::s52_core_headless::build_feature_portrayal_ir(*lookup_index, trflne_feature, mariner_settings);
    if(trflne_ir.line_styles.size() != 1
        || trflne_ir.line_styles.front().line_style_name != "DASH"
        || trflne_ir.display_priorities.size() != 1
        || trflne_ir.display_priorities.front().source_name != "Area Symbol"
        || trflne_ir.instruction_count() != 2) {
        return 3;
    }

    marine_chart::s52_core_headless::RuleLayerFeature unsare_feature;
    unsare_feature.object_class = "UNSARE";
    unsare_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;
    const auto unsare_ir =
        marine_chart::s52_core_headless::build_feature_portrayal_ir(*lookup_index, unsare_feature, mariner_settings);
    if(unsare_ir.area_patterns.size() != 1
        || unsare_ir.area_patterns.front().pattern_name != "NODATA03"
        || unsare_ir.display_priorities.size() != 1
        || unsare_ir.display_priorities.front().source_name != "No data"
        || unsare_ir.instruction_count() != 2) {
        return 4;
    }

    marine_chart::s52_core_headless::RuleLayerFeature seaare_feature;
    seaare_feature.object_class = "SEAARE";
    seaare_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;
    const auto seaare_ir =
        marine_chart::s52_core_headless::build_feature_portrayal_ir(*lookup_index, seaare_feature, mariner_settings);
    if(seaare_ir.text_rules.size() != 1
        || seaare_ir.text_rules.front().instruction_text != "TX(OBJNAM,1,2,3,'15110',0,0,CHBLK,26)"
        || seaare_ir.display_priorities.size() != 1
        || seaare_ir.display_priorities.front().source_name != "Area 2"
        || seaare_ir.instruction_count() != 2) {
        return 5;
    }

    marine_chart::s52_core_headless::RuleLayerFeature achare_feature;
    achare_feature.object_class = "ACHARE";
    achare_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;
    const auto achare_ir =
        marine_chart::s52_core_headless::build_feature_portrayal_ir(*lookup_index, achare_feature, mariner_settings);
    if(!achare_ir.empty()) {
        return 6;
    }

    return 0;
}
