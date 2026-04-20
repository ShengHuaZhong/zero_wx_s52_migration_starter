#pragma once

#include "marine_chart/s52_core_headless/neutral_string.h"

namespace marine_chart::s52_core_headless {

struct ModuleInfo final {
    NeutralString name;
    NeutralString responsibility;
};

[[nodiscard]] ModuleInfo describe_module() noexcept;

}  // namespace marine_chart::s52_core_headless
