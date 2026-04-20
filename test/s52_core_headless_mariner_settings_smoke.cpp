#include "marine_chart/s52_core_headless/mariner_settings.h"

int main() {
    const auto defaults = marine_chart::s52_core_headless::make_default_mariner_settings();
    if(!defaults.valid()) {
        return 1;
    }

    if(defaults.display_category != marine_chart::s52_core_headless::DisplayCategory::standard) {
        return 2;
    }

    if(defaults.point_symbol_style != marine_chart::s52_core_headless::PointSymbolStyle::simplified) {
        return 3;
    }

    if(defaults.area_boundary_style != marine_chart::s52_core_headless::AreaBoundaryStyle::plain) {
        return 4;
    }

    if(defaults.shallow_contour_depth_meters != 2.0
        || defaults.safety_contour_depth_meters != 3.0
        || defaults.safety_depth_meters != 3.0
        || defaults.deep_contour_depth_meters != 30.0) {
        return 5;
    }

    if(defaults.two_shades || !defaults.show_soundings || !defaults.show_text || defaults.show_national_text
        || !defaults.use_scamin) {
        return 6;
    }

    auto customized = defaults;
    customized.display_category = marine_chart::s52_core_headless::DisplayCategory::other;
    customized.point_symbol_style = marine_chart::s52_core_headless::PointSymbolStyle::paper_chart;
    customized.area_boundary_style = marine_chart::s52_core_headless::AreaBoundaryStyle::symbolized;
    customized.shallow_contour_depth_meters = 1.0;
    customized.safety_contour_depth_meters = 5.0;
    customized.safety_depth_meters = 4.0;
    customized.deep_contour_depth_meters = 12.0;
    customized.two_shades = true;
    customized.show_soundings = false;
    customized.show_text = false;
    customized.show_national_text = true;
    customized.use_scamin = false;

    if(!customized.valid()) {
        return 7;
    }

    if(customized.display_category != marine_chart::s52_core_headless::DisplayCategory::other
        || customized.point_symbol_style != marine_chart::s52_core_headless::PointSymbolStyle::paper_chart
        || customized.area_boundary_style != marine_chart::s52_core_headless::AreaBoundaryStyle::symbolized) {
        return 8;
    }

    auto invalid = customized;
    invalid.deep_contour_depth_meters = 0.5;
    if(invalid.valid()) {
        return 9;
    }

    return 0;
}
