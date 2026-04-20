#include "marine_chart/s52_core_headless/feature_attribute_adapter.h"

int main() {
    marine_chart::s52_core_headless::RuleLayerFeature feature;
    feature.object_class = "LIGHTS";
    feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::point;
    feature.attributes.emplace(
        "OBJNAM",
        marine_chart::s52_core_headless::NeutralVector<marine_chart::s52_core_headless::NeutralString>{
            "Approach Light"});
    feature.attributes.emplace(
        "CATLIT",
        marine_chart::s52_core_headless::NeutralVector<marine_chart::s52_core_headless::NeutralString>{
            "1",
            "2"});
    feature.attributes.emplace(
        "SCAMIN",
        marine_chart::s52_core_headless::NeutralVector<marine_chart::s52_core_headless::NeutralString>{
            "50000"});

    if(feature.empty()) {
        return 1;
    }

    const auto* object_name_values =
        marine_chart::s52_core_headless::find_feature_attribute(feature, "OBJNAM");
    if(object_name_values == nullptr || object_name_values->size() != 1 || object_name_values->front() != "Approach Light") {
        return 2;
    }

    const auto scamin_value =
        marine_chart::s52_core_headless::find_feature_attribute_first_value(feature, "SCAMIN");
    if(!scamin_value.has_value() || *scamin_value != "50000") {
        return 3;
    }

    if(!marine_chart::s52_core_headless::feature_has_attribute_value(feature, "CATLIT", "2")) {
        return 4;
    }

    if(marine_chart::s52_core_headless::feature_has_attribute_value(feature, "CATLIT", "9")) {
        return 5;
    }

    if(marine_chart::s52_core_headless::find_feature_attribute(feature, "MISSING") != nullptr) {
        return 6;
    }

    marine_chart::s52_core_headless::RuleLayerFeature invalid_feature;
    invalid_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::line;
    if(!invalid_feature.empty()) {
        return 7;
    }

    invalid_feature.object_class = "COALNE";
    invalid_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::line;
    if(invalid_feature.empty()) {
        return 8;
    }

    return 0;
}
