#pragma once

#include "marine_chart/s52_core_headless/neutral_color.h"
#include "marine_chart/s52_core_headless/neutral_containers.h"
#include "marine_chart/s52_core_headless/neutral_geometry.h"
#include "marine_chart/s52_core_headless/neutral_string.h"

namespace marine_chart::s52_core_headless {

struct ModuleInfo final {
    NeutralString name;
    NeutralString responsibility;
    NeutralColor accent_color;
    NeutralRect default_viewport;
    NeutralVector<NeutralString> capability_tags;
    NeutralMap<NeutralString, NeutralString> defaults;
};

[[nodiscard]] ModuleInfo describe_module() noexcept;

}  // namespace marine_chart::s52_core_headless
