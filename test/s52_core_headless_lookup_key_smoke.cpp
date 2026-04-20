#include "marine_chart/s52_core_headless/lookup_index.h"
#include "marine_chart/s52_core_headless/lookup_key.h"

int main() {
    marine_chart::s52_core_headless::RuleLayerFeature point_feature;
    point_feature.object_class = "TOPMAR";
    point_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::point;

    auto mariner_settings = marine_chart::s52_core_headless::make_default_mariner_settings();
    const auto simplified_key =
        marine_chart::s52_core_headless::make_lookup_key(point_feature, mariner_settings);
    if(!simplified_key.has_value()
        || simplified_key->lookup_type != "Point"
        || simplified_key->table_name != "Simplified") {
        return 1;
    }

    mariner_settings.point_symbol_style = marine_chart::s52_core_headless::PointSymbolStyle::paper_chart;
    const auto paper_key = marine_chart::s52_core_headless::make_lookup_key(point_feature, mariner_settings);
    if(!paper_key.has_value()
        || paper_key->lookup_type != "Point"
        || paper_key->table_name != "Paper") {
        return 2;
    }

    marine_chart::s52_core_headless::RuleLayerFeature area_feature;
    area_feature.object_class = "ACHARE";
    area_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;

    mariner_settings = marine_chart::s52_core_headless::make_default_mariner_settings();
    const auto plain_key = marine_chart::s52_core_headless::make_lookup_key(area_feature, mariner_settings);
    if(!plain_key.has_value() || plain_key->table_name != "Plain") {
        return 3;
    }

    mariner_settings.area_boundary_style = marine_chart::s52_core_headless::AreaBoundaryStyle::symbolized;
    const auto symbolized_key =
        marine_chart::s52_core_headless::make_lookup_key(area_feature, mariner_settings);
    if(!symbolized_key.has_value() || symbolized_key->table_name != "Symbolized") {
        return 4;
    }

    marine_chart::s52_core_headless::RuleLayerFeature line_feature;
    line_feature.object_class = "DEPCNT";
    line_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::line;
    const auto line_key = marine_chart::s52_core_headless::make_lookup_key(
        line_feature,
        marine_chart::s52_core_headless::make_default_mariner_settings());
    if(!line_key.has_value()
        || line_key->lookup_type != "Line"
        || line_key->table_name != "Lines") {
        return 5;
    }

    const auto lookup_index =
        marine_chart::s52_core_headless::build_lookup_index_from_asset_root("vendor/opencpn_s57data");
    if(!lookup_index.has_value() || lookup_index->empty()) {
        return 6;
    }

    const auto* point_bucket = marine_chart::s52_core_headless::find_lookup_index_bucket(
        *lookup_index,
        paper_key->object_class,
        paper_key->lookup_type,
        paper_key->table_name);
    if(point_bucket == nullptr) {
        return 7;
    }

    const auto* area_bucket = marine_chart::s52_core_headless::find_lookup_index_bucket(
        *lookup_index,
        plain_key->object_class,
        plain_key->lookup_type,
        plain_key->table_name);
    if(area_bucket == nullptr) {
        return 8;
    }

    marine_chart::s52_core_headless::RuleLayerFeature invalid_feature;
    invalid_feature.object_class = "LIGHTS";
    if(marine_chart::s52_core_headless::make_lookup_key(
           invalid_feature,
           marine_chart::s52_core_headless::make_default_mariner_settings())
        .has_value()) {
        return 9;
    }

    return 0;
}
