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

    return 0;
}
