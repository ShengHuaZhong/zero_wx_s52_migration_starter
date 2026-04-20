#include "marine_chart/s52_core_headless/csp_entry_audit.h"

int main() {
    const auto raw_catalog =
        marine_chart::s52_core_headless::load_lookup_raw_catalog_from_asset_root("vendor/opencpn_s57data");
    if(!raw_catalog.has_value() || raw_catalog->empty()) {
        return 1;
    }

    const auto audit = marine_chart::s52_core_headless::audit_csp_entries(*raw_catalog);
    if(!audit.has_value() || audit->empty()) {
        return 2;
    }

    if(audit->entries.size() != 22) {
        return 3;
    }

    if(audit->entries.front().name != "CLRLIN01" || audit->entries.front().count != 1) {
        return 4;
    }

    const auto* restrn = marine_chart::s52_core_headless::find_csp_entry_usage(*audit, "RESTRN01");
    if(restrn == nullptr || restrn->count != 67) {
        return 5;
    }

    const auto* topmar = marine_chart::s52_core_headless::find_csp_entry_usage(*audit, "TOPMAR01");
    if(topmar == nullptr || topmar->count != 53) {
        return 6;
    }

    const auto* lights = marine_chart::s52_core_headless::find_csp_entry_usage(*audit, "LIGHTS05");
    if(lights == nullptr || lights->count != 6) {
        return 7;
    }

    const auto* topmari1 = marine_chart::s52_core_headless::find_csp_entry_usage(*audit, "TOPMARI1");
    if(topmari1 == nullptr || topmari1->count != 1) {
        return 8;
    }

    if(marine_chart::s52_core_headless::find_csp_entry_usage(*audit, "NOTREAL01") != nullptr) {
        return 9;
    }

    const auto audit_from_asset_root =
        marine_chart::s52_core_headless::audit_csp_entries_from_asset_root("vendor/opencpn_s57data");
    if(!audit_from_asset_root.has_value()
        || audit_from_asset_root->entries.size() != audit->entries.size()) {
        return 10;
    }

    return 0;
}
