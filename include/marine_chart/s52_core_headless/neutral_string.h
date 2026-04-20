#pragma once

#include <string>
#include <string_view>

namespace marine_chart::s52_core_headless {

using NeutralString = std::string;
using NeutralStringView = std::string_view;

[[nodiscard]] inline NeutralString make_neutral_string(NeutralStringView text) {
    return NeutralString{text};
}

[[nodiscard]] inline NeutralStringView as_string_view(const NeutralString& text) noexcept {
    return NeutralStringView{text};
}

}  // namespace marine_chart::s52_core_headless
