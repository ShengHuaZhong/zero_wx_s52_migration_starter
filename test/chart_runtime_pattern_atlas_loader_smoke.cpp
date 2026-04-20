#include "marine_chart/chart_runtime/pattern_atlas_loader.h"
#include "marine_chart/s52_core_headless/headless_core_init.h"

int main() {
    const auto initialization = marine_chart::s52_core_headless::initialize_headless_core("vendor/opencpn_s57data");
    if(!initialization.has_value() || !initialization->valid()) {
        return 1;
    }

    marine_chart::chart_runtime::AreaPatternIR area_pattern_ir;
    area_pattern_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::area_pattern;
    area_pattern_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::area;
    area_pattern_ir.instruction.stable_id = "area-pattern:AIRARE:77";
    area_pattern_ir.instruction.source.object_class = "AIRARE";
    area_pattern_ir.instruction.source.lookup_type = "Area";
    area_pattern_ir.instruction.source.table_name = "Plain";
    area_pattern_ir.instruction.source.lookup_id = "77";
    area_pattern_ir.pattern_name = "AIRARE02";
    area_pattern_ir.boundary_line_style_name = "SOLD";

    const auto atlas_entry =
        marine_chart::chart_runtime::load_pattern_atlas_entry(initialization->asset_catalogs, "DAY_BRIGHT", area_pattern_ir);
    if(!atlas_entry.has_value() || atlas_entry->pattern_name != "AIRARE02"
        || atlas_entry->palette_name != "DAY_BRIGHT"
        || atlas_entry->graphics_file_name != "rastersymbols-day.png"
        || atlas_entry->tile_width <= 0
        || atlas_entry->tile_height <= 0
        || atlas_entry->color_token.empty()
        || atlas_entry->pattern_source.empty()) {
        return 2;
    }

    if(marine_chart::chart_runtime::load_pattern_atlas_entry(
           initialization->asset_catalogs,
           "UNKNOWN",
           area_pattern_ir)
           .has_value()) {
        return 3;
    }

    marine_chart::chart_runtime::AreaPatternIR invalid_ir = area_pattern_ir;
    invalid_ir.pattern_name = "UNKNOWN";
    if(marine_chart::chart_runtime::load_pattern_atlas_entry(
           initialization->asset_catalogs,
           "DAY_BRIGHT",
           invalid_ir)
           .has_value()) {
        return 4;
    }

    return 0;
}
