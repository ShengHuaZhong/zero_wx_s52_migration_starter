#include "marine_chart/s52_core_headless/neutral_config_loader.h"
#include "marine_chart/s52_core_headless/module.h"

#include <string_view>

int main() {
    const auto neutral_string = marine_chart::s52_core_headless::make_neutral_string("core");
    if(neutral_string != "core") {
        return 1;
    }

    if(marine_chart::s52_core_headless::as_string_view(neutral_string) != "core") {
        return 2;
    }

    const auto module_info = marine_chart::s52_core_headless::describe_module();

    if(module_info.name != "s52_core_headless") {
        return 3;
    }

    if(module_info.responsibility.find("Zero-wx") == std::string_view::npos) {
        return 4;
    }

    const auto expected_color = marine_chart::s52_core_headless::make_neutral_color(24, 64, 128);
    if(module_info.accent_color != expected_color) {
        return 5;
    }

    if(!module_info.accent_color.is_opaque()) {
        return 6;
    }

    const auto expected_viewport = marine_chart::s52_core_headless::make_neutral_rect(10, 20, 640, 480);
    if(module_info.default_viewport != expected_viewport) {
        return 7;
    }

    if(!module_info.default_viewport.contains(
        marine_chart::s52_core_headless::make_neutral_point(100, 100))) {
        return 8;
    }

    if(module_info.default_viewport.contains(
        marine_chart::s52_core_headless::make_neutral_point(0, 0))) {
        return 9;
    }

    if(module_info.default_viewport.is_empty()) {
        return 10;
    }

    if(module_info.capability_tags.size() != 2) {
        return 11;
    }

    if(module_info.capability_tags.front() != "headless") {
        return 12;
    }

    const auto render_path = module_info.defaults.find("render-path");
    if(render_path == module_info.defaults.end()) {
        return 13;
    }

    if(render_path->second != "rhi") {
        return 14;
    }

    const auto config = marine_chart::s52_core_headless::load_neutral_config_from_text(
        "# module defaults\n"
        "render-path = rhi\n"
        "role = portrayal-core\n");
    const auto config_render_path = marine_chart::s52_core_headless::find_config_value(config, "render-path");
    if(!config_render_path.has_value()) {
        return 15;
    }

    if(*config_render_path != "rhi") {
        return 16;
    }

    const auto missing_value = marine_chart::s52_core_headless::find_config_value(config, "missing");
    if(missing_value.has_value()) {
        return 17;
    }

    return 0;
}
