#pragma once

#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <string_view>

namespace marine_chart::chart_runtime {

struct RuntimeColor final {
    std::uint8_t red{0};
    std::uint8_t green{0};
    std::uint8_t blue{0};
    std::uint8_t alpha{255};

    bool operator==(const RuntimeColor&) const noexcept = default;
};

[[nodiscard]] inline RuntimeColor make_runtime_color(
    std::uint8_t red,
    std::uint8_t green,
    std::uint8_t blue,
    std::uint8_t alpha = 255) noexcept {
    return RuntimeColor{red, green, blue, alpha};
}

struct RuntimePaletteColors final {
    std::string palette_name;
    std::string graphics_file_name;
    std::map<std::string, RuntimeColor, std::less<>> entries;

    [[nodiscard]] bool empty() const noexcept {
        return palette_name.empty() || graphics_file_name.empty() || entries.empty();
    }

    bool operator==(const RuntimePaletteColors&) const noexcept = default;
};

[[nodiscard]] std::optional<RuntimeColor> find_runtime_palette_color(
    const RuntimePaletteColors& palette,
    std::string_view color_token) noexcept;

}  // namespace marine_chart::chart_runtime
