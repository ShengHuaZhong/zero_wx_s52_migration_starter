#pragma once

#include <cstdint>

namespace marine_chart::s52_core_headless {

enum class DisplayCategory : std::uint8_t {
    display_base,
    standard,
    other
};

enum class PointSymbolStyle : std::uint8_t {
    simplified,
    paper_chart
};

enum class AreaBoundaryStyle : std::uint8_t {
    plain,
    symbolized
};

struct MarinerSettings final {
    DisplayCategory display_category{DisplayCategory::standard};
    PointSymbolStyle point_symbol_style{PointSymbolStyle::simplified};
    AreaBoundaryStyle area_boundary_style{AreaBoundaryStyle::plain};
    double shallow_contour_depth_meters{2.0};
    double safety_contour_depth_meters{3.0};
    double safety_depth_meters{3.0};
    double deep_contour_depth_meters{30.0};
    bool two_shades{false};
    bool show_soundings{true};
    bool show_text{true};
    bool show_national_text{false};
    bool use_scamin{true};

    [[nodiscard]] constexpr bool valid() const noexcept {
        return shallow_contour_depth_meters >= 0.0
            && safety_contour_depth_meters >= 0.0
            && safety_depth_meters >= 0.0
            && deep_contour_depth_meters >= 0.0
            && shallow_contour_depth_meters <= deep_contour_depth_meters
            && safety_contour_depth_meters <= deep_contour_depth_meters
            && safety_depth_meters <= deep_contour_depth_meters;
    }

    bool operator==(const MarinerSettings&) const noexcept = default;
};

[[nodiscard]] constexpr MarinerSettings make_default_mariner_settings() noexcept {
    return {};
}

}  // namespace marine_chart::s52_core_headless
