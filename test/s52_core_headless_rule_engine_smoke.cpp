#include "marine_chart/chart_runtime/portrayal_ir_debug_dump.h"
#include "marine_chart/s52_core_headless/portrayal_ir_pipeline.h"

#include <string>

int main() {
    const auto lookup_index =
        marine_chart::s52_core_headless::build_lookup_index_from_asset_root("vendor/opencpn_s57data");
    if(!lookup_index.has_value() || lookup_index->empty()) {
        return 1;
    }

    const auto mariner_settings = marine_chart::s52_core_headless::make_default_mariner_settings();

    marine_chart::s52_core_headless::RuleLayerFeature achpnt_feature;
    achpnt_feature.object_class = "ACHPNT";
    achpnt_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::point;

    marine_chart::s52_core_headless::RuleLayerFeature trflne_feature;
    trflne_feature.object_class = "TRFLNE";
    trflne_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::line;

    marine_chart::s52_core_headless::RuleLayerFeature unsare_feature;
    unsare_feature.object_class = "UNSARE";
    unsare_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;

    marine_chart::s52_core_headless::RuleLayerFeature seaare_feature;
    seaare_feature.object_class = "SEAARE";
    seaare_feature.primitive_type = marine_chart::s52_core_headless::FeaturePrimitiveType::area;

    const auto achpnt_ir =
        marine_chart::s52_core_headless::build_feature_portrayal_ir(*lookup_index, achpnt_feature, mariner_settings);
    const auto trflne_ir =
        marine_chart::s52_core_headless::build_feature_portrayal_ir(*lookup_index, trflne_feature, mariner_settings);
    const auto unsare_ir =
        marine_chart::s52_core_headless::build_feature_portrayal_ir(*lookup_index, unsare_feature, mariner_settings);
    const auto seaare_ir =
        marine_chart::s52_core_headless::build_feature_portrayal_ir(*lookup_index, seaare_feature, mariner_settings);

    const auto total_instruction_count = achpnt_ir.instruction_count() + trflne_ir.instruction_count()
        + unsare_ir.instruction_count() + seaare_ir.instruction_count();
    if(total_instruction_count != 8) {
        return 2;
    }

    std::string debug_dump;
    debug_dump += marine_chart::chart_runtime::dump_feature_portrayal_ir(achpnt_ir);
    debug_dump += marine_chart::chart_runtime::dump_feature_portrayal_ir(trflne_ir);
    debug_dump += marine_chart::chart_runtime::dump_feature_portrayal_ir(unsare_ir);
    debug_dump += marine_chart::chart_runtime::dump_feature_portrayal_ir(seaare_ir);

    if(debug_dump.find("symbol=ACHPNT01") == std::string::npos) {
        return 3;
    }

    if(debug_dump.find("style=DASH") == std::string::npos) {
        return 4;
    }

    if(debug_dump.find("pattern=NODATA03") == std::string::npos || debug_dump.find("boundary=SOLD") == std::string::npos) {
        return 5;
    }

    if(debug_dump.find("text=TX(OBJNAM,1,2,3,'15110',0,0,CHBLK,26)") == std::string::npos) {
        return 6;
    }

    if(debug_dump.find("source=Hazards") == std::string::npos || debug_dump.find("source=Area Symbol") == std::string::npos
        || debug_dump.find("source=No data") == std::string::npos
        || debug_dump.find("source=Area 2") == std::string::npos) {
        return 7;
    }

    return 0;
}
