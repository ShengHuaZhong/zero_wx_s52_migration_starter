#pragma once

#include "marine_chart/s52_core_headless/neutral_containers.h"
#include "marine_chart/s52_core_headless/neutral_string.h"

#include <cstdint>

namespace marine_chart::s52_core_headless {

enum class FeaturePrimitiveType : std::uint8_t {
    unknown,
    point,
    line,
    area
};

struct RuleLayerFeature final {
    NeutralString object_class;
    FeaturePrimitiveType primitive_type{FeaturePrimitiveType::unknown};
    NeutralMap<NeutralString, NeutralVector<NeutralString>> attributes;

    [[nodiscard]] bool empty() const noexcept {
        return object_class.empty() || primitive_type == FeaturePrimitiveType::unknown;
    }

    bool operator==(const RuleLayerFeature&) const noexcept = default;
};

[[nodiscard]] const NeutralVector<NeutralString>* find_feature_attribute(
    const RuleLayerFeature& feature,
    NeutralStringView attribute_name) noexcept;

[[nodiscard]] NeutralOptional<NeutralString> find_feature_attribute_first_value(
    const RuleLayerFeature& feature,
    NeutralStringView attribute_name);

[[nodiscard]] bool feature_has_attribute_value(
    const RuleLayerFeature& feature,
    NeutralStringView attribute_name,
    NeutralStringView attribute_value) noexcept;

}  // namespace marine_chart::s52_core_headless
