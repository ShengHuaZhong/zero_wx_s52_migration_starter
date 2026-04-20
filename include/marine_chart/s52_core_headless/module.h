#pragma once

#include <string_view>

namespace marine_chart::s52_core_headless {

struct ModuleInfo final {
    std::string_view name;
    std::string_view responsibility;
};

[[nodiscard]] ModuleInfo describe_module() noexcept;

}  // namespace marine_chart::s52_core_headless
