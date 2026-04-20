#include "marine_chart/s52_core_headless/module.h"

#include <string_view>

int main() {
    const auto module_info = marine_chart::s52_core_headless::describe_module();

    if(module_info.name != "s52_core_headless") {
        return 1;
    }

    if(module_info.responsibility.find("Zero-wx") == std::string_view::npos) {
        return 2;
    }

    return 0;
}
