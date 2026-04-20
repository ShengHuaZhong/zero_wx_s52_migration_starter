#include "marine_chart/s52_core_headless/feature_attribute_adapter.h"

namespace marine_chart::s52_core_headless {

const NeutralVector<NeutralString>* find_feature_attribute(
    const RuleLayerFeature& feature,
    NeutralStringView attribute_name) noexcept {
    const auto match = feature.attributes.find(make_neutral_string(attribute_name));
    if(match == feature.attributes.end()) {
        return nullptr;
    }

    return &match->second;
}

NeutralOptional<NeutralString> find_feature_attribute_first_value(
    const RuleLayerFeature& feature,
    NeutralStringView attribute_name) {
    const auto* values = find_feature_attribute(feature, attribute_name);
    if(values == nullptr || values->empty()) {
        return std::nullopt;
    }

    return values->front();
}

bool feature_has_attribute_value(
    const RuleLayerFeature& feature,
    NeutralStringView attribute_name,
    NeutralStringView attribute_value) noexcept {
    const auto* values = find_feature_attribute(feature, attribute_name);
    if(values == nullptr) {
        return false;
    }

    for(const auto& value : *values) {
        if(value == attribute_value) {
            return true;
        }
    }

    return false;
}

}  // namespace marine_chart::s52_core_headless
