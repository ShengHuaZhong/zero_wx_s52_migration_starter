#include "marine_chart/chart_runtime/runtime_palette_colors.h"

namespace marine_chart::chart_runtime {

std::optional<RuntimeColor> find_runtime_palette_color(
    const RuntimePaletteColors& palette,
    std::string_view color_token) noexcept {
    if(palette.empty() || color_token.empty()) {
        return std::nullopt;
    }

    const auto match = palette.entries.find(color_token);
    if(match == palette.entries.end()) {
        return std::nullopt;
    }

    return match->second;
}

}  // namespace marine_chart::chart_runtime
