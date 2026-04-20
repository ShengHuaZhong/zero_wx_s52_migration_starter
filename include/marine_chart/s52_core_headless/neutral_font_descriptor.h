#pragma once

#include "marine_chart/s52_core_headless/neutral_string.h"

#include <cstdint>

namespace marine_chart::s52_core_headless {

enum class FontWeight {
    normal,
    bold
};

enum class FontSlant {
    normal,
    italic
};

struct NeutralFontDescriptor final {
    NeutralString family_name;
    std::int32_t point_size{0};
    FontWeight weight{FontWeight::normal};
    FontSlant slant{FontSlant::normal};
    bool underline{false};
    bool strikeout{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return point_size > 0;
    }

    constexpr bool operator==(const NeutralFontDescriptor&) const noexcept = default;
};

[[nodiscard]] inline NeutralFontDescriptor make_neutral_font_descriptor(
    NeutralStringView family_name,
    std::int32_t point_size,
    FontWeight weight = FontWeight::normal,
    FontSlant slant = FontSlant::normal,
    bool underline = false,
    bool strikeout = false) {
    return NeutralFontDescriptor{
        make_neutral_string(family_name),
        point_size,
        weight,
        slant,
        underline,
        strikeout
    };
}

}  // namespace marine_chart::s52_core_headless
