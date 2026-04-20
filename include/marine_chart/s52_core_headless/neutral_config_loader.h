#pragma once

#include "marine_chart/s52_core_headless/neutral_containers.h"
#include "marine_chart/s52_core_headless/neutral_string.h"

namespace marine_chart::s52_core_headless {

struct NeutralConfigDocument final {
    NeutralMap<NeutralString, NeutralString> values;
};

[[nodiscard]] NeutralConfigDocument load_neutral_config_from_text(NeutralStringView text);

[[nodiscard]] NeutralOptional<NeutralString> find_config_value(
    const NeutralConfigDocument& document,
    NeutralStringView key);

}  // namespace marine_chart::s52_core_headless
