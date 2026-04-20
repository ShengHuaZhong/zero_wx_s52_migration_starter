#pragma once

#include <cstdint>

namespace marine_chart::s52_core_headless {

struct NeutralColor final {
    std::uint8_t red{0};
    std::uint8_t green{0};
    std::uint8_t blue{0};
    std::uint8_t alpha{255};

    [[nodiscard]] constexpr bool is_opaque() const noexcept {
        return alpha == 255;
    }

    [[nodiscard]] constexpr bool is_transparent() const noexcept {
        return alpha == 0;
    }

    constexpr bool operator==(const NeutralColor&) const noexcept = default;
};

[[nodiscard]] constexpr NeutralColor make_neutral_color(
    std::uint8_t red,
    std::uint8_t green,
    std::uint8_t blue,
    std::uint8_t alpha = 255) noexcept {
    return NeutralColor{red, green, blue, alpha};
}

}  // namespace marine_chart::s52_core_headless
