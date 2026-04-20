#include "marine_chart/chart_runtime/s57_dataset_ingestion.h"

#include <cstdlib>

int main() {
    const char* dataset_root = std::getenv("S57_TESTDATA_ROOT");
    if(dataset_root == nullptr || dataset_root[0] == '\0') {
        return 125;
    }

    const auto loaded_dataset =
        marine_chart::chart_runtime::load_rule_layer_features_from_s57_dataset(dataset_root, "vendor/opencpn_s57data");
    if(!loaded_dataset.has_value() || !loaded_dataset->valid()) {
        return 1;
    }

    bool has_point = false;
    bool has_line = false;
    bool has_area = false;
    for(const auto& feature : loaded_dataset->features) {
        if(feature.primitive_type == marine_chart::s52_core_headless::FeaturePrimitiveType::point) {
            has_point = true;
        } else if(feature.primitive_type == marine_chart::s52_core_headless::FeaturePrimitiveType::line) {
            has_line = true;
        } else if(feature.primitive_type == marine_chart::s52_core_headless::FeaturePrimitiveType::area) {
            has_area = true;
        }
    }

    if(!has_point || !has_line || !has_area) {
        return 2;
    }

    if(loaded_dataset->frid_record_count < loaded_dataset->features.size()) {
        return 3;
    }

    return 0;
}
