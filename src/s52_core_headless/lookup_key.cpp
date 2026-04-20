#include "marine_chart/s52_core_headless/lookup_key.h"

namespace marine_chart::s52_core_headless {
namespace {

[[nodiscard]] NeutralOptional<NeutralString> resolve_lookup_type(FeaturePrimitiveType primitive_type) {
    switch(primitive_type) {
    case FeaturePrimitiveType::point:
        return make_neutral_string("Point");
    case FeaturePrimitiveType::line:
        return make_neutral_string("Line");
    case FeaturePrimitiveType::area:
        return make_neutral_string("Area");
    case FeaturePrimitiveType::unknown:
        break;
    }

    return std::nullopt;
}

[[nodiscard]] NeutralOptional<NeutralString> resolve_table_name(
    FeaturePrimitiveType primitive_type,
    const MarinerSettings& mariner_settings) {
    switch(primitive_type) {
    case FeaturePrimitiveType::point:
        return mariner_settings.point_symbol_style == PointSymbolStyle::paper_chart
            ? make_neutral_string("Paper")
            : make_neutral_string("Simplified");
    case FeaturePrimitiveType::line:
        return make_neutral_string("Lines");
    case FeaturePrimitiveType::area:
        return mariner_settings.area_boundary_style == AreaBoundaryStyle::symbolized
            ? make_neutral_string("Symbolized")
            : make_neutral_string("Plain");
    case FeaturePrimitiveType::unknown:
        break;
    }

    return std::nullopt;
}

}  // namespace

NeutralOptional<LookupKey> make_lookup_key(
    const RuleLayerFeature& feature,
    const MarinerSettings& mariner_settings) {
    if(feature.empty()) {
        return std::nullopt;
    }

    const auto lookup_type = resolve_lookup_type(feature.primitive_type);
    const auto table_name = resolve_table_name(feature.primitive_type, mariner_settings);
    if(!lookup_type.has_value() || !table_name.has_value()) {
        return std::nullopt;
    }

    LookupKey key;
    key.object_class = feature.object_class;
    key.lookup_type = *lookup_type;
    key.table_name = *table_name;

    if(key.empty()) {
        return std::nullopt;
    }

    return key;
}

}  // namespace marine_chart::s52_core_headless
