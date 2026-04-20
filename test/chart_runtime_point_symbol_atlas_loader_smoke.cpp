#include "marine_chart/chart_runtime/point_symbol_atlas_loader.h"
#include "marine_chart/s52_core_headless/headless_core_init.h"

int main() {
    const auto initialization = marine_chart::s52_core_headless::initialize_headless_core("vendor/opencpn_s57data");
    if(!initialization.has_value() || !initialization->valid()) {
        return 1;
    }

    marine_chart::chart_runtime::PointSymbolIR point_symbol_ir;
    point_symbol_ir.instruction.kind = marine_chart::chart_runtime::InstructionKind::point_symbol;
    point_symbol_ir.instruction.primitive = marine_chart::chart_runtime::PrimitiveKind::point;
    point_symbol_ir.instruction.stable_id = "point-symbol:ACHPNT:42";
    point_symbol_ir.instruction.source.object_class = "ACHPNT";
    point_symbol_ir.instruction.source.lookup_type = "Point";
    point_symbol_ir.instruction.source.table_name = "Simplified";
    point_symbol_ir.instruction.source.lookup_id = "42";
    point_symbol_ir.symbol_name = "ACHPNT01";

    const auto atlas_entry =
        marine_chart::chart_runtime::load_point_symbol_atlas_entry(initialization->asset_catalogs, "DAY_BRIGHT", point_symbol_ir);
    if(!atlas_entry.has_value() || atlas_entry->symbol_name != "ACHPNT01"
        || atlas_entry->palette_name != "DAY_BRIGHT"
        || atlas_entry->graphics_file_name != "rastersymbols-day.png"
        || atlas_entry->source_width <= 0
        || atlas_entry->source_height <= 0
        || atlas_entry->color_token.empty()) {
        return 2;
    }

    if(marine_chart::chart_runtime::load_point_symbol_atlas_entry(
           initialization->asset_catalogs,
           "UNKNOWN",
           point_symbol_ir)
           .has_value()) {
        return 3;
    }

    marine_chart::chart_runtime::PointSymbolIR invalid_ir = point_symbol_ir;
    invalid_ir.symbol_name = "UNKNOWN";
    if(marine_chart::chart_runtime::load_point_symbol_atlas_entry(
           initialization->asset_catalogs,
           "DAY_BRIGHT",
           invalid_ir)
           .has_value()) {
        return 4;
    }

    return 0;
}
