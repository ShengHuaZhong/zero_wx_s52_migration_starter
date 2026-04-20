#pragma once

#include <cstdint>

namespace marine_chart::s52_core_headless {

struct NeutralPoint final {
    std::int32_t x{0};
    std::int32_t y{0};

    constexpr bool operator==(const NeutralPoint&) const noexcept = default;
};

struct NeutralSize final {
    std::int32_t width{0};
    std::int32_t height{0};

    [[nodiscard]] constexpr bool is_empty() const noexcept {
        return width <= 0 || height <= 0;
    }

    constexpr bool operator==(const NeutralSize&) const noexcept = default;
};

struct NeutralRect final {
    NeutralPoint origin{};
    NeutralSize size{};

    [[nodiscard]] constexpr bool is_empty() const noexcept {
        return size.is_empty();
    }

    [[nodiscard]] constexpr bool contains(NeutralPoint point) const noexcept {
        return point.x >= origin.x
            && point.y >= origin.y
            && point.x < origin.x + size.width
            && point.y < origin.y + size.height;
    }

    constexpr bool operator==(const NeutralRect&) const noexcept = default;
};

[[nodiscard]] constexpr NeutralPoint make_neutral_point(std::int32_t x, std::int32_t y) noexcept {
    return NeutralPoint{x, y};
}

[[nodiscard]] constexpr NeutralSize make_neutral_size(std::int32_t width, std::int32_t height) noexcept {
    return NeutralSize{width, height};
}

[[nodiscard]] constexpr NeutralRect make_neutral_rect(
    std::int32_t x,
    std::int32_t y,
    std::int32_t width,
    std::int32_t height) noexcept {
    return NeutralRect{
        make_neutral_point(x, y),
        make_neutral_size(width, height)
    };
}

}  // namespace marine_chart::s52_core_headless
