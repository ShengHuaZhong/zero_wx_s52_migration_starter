#include "marine_chart/chart_runtime/runtime_palette_colors.h"

int main() {
    marine_chart::chart_runtime::RuntimePaletteColors palette;
    palette.palette_name = "DAY_BRIGHT";
    palette.graphics_file_name = "rastersymbols-day.png";
    palette.entries.emplace("CHBLK", marine_chart::chart_runtime::make_runtime_color(18, 18, 18));
    palette.entries.emplace("DEPDW", marine_chart::chart_runtime::make_runtime_color(186, 210, 238));

    const auto black = marine_chart::chart_runtime::find_runtime_palette_color(palette, "CHBLK");
    if(!black.has_value() || *black != marine_chart::chart_runtime::make_runtime_color(18, 18, 18)) {
        return 1;
    }

    const auto depdw = marine_chart::chart_runtime::find_runtime_palette_color(palette, "DEPDW");
    if(!depdw.has_value() || *depdw != marine_chart::chart_runtime::make_runtime_color(186, 210, 238)) {
        return 2;
    }

    if(marine_chart::chart_runtime::find_runtime_palette_color(palette, "UNKNOWN").has_value()) {
        return 3;
    }

    marine_chart::chart_runtime::RuntimePaletteColors empty_palette;
    if(marine_chart::chart_runtime::find_runtime_palette_color(empty_palette, "CHBLK").has_value()) {
        return 4;
    }

    return 0;
}
