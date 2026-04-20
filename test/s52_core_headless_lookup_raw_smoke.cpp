#include "marine_chart/s52_core_headless/chartsymbols_xml_loader.h"
#include "marine_chart/s52_core_headless/lookup_raw_loader.h"

#include <algorithm>

int main() {
    const auto lookup_catalog =
        marine_chart::s52_core_headless::load_lookup_raw_catalog_from_asset_root("vendor/opencpn_s57data");
    if(!lookup_catalog.has_value() || lookup_catalog->empty()) {
        return 1;
    }

    if(lookup_catalog->entries.size() != 3057) {
        return 2;
    }

    const auto& first_entry = lookup_catalog->entries.front();
    if(first_entry.id != "0" || first_entry.rcid != "32036" || first_entry.name != "######") {
        return 3;
    }

    if(first_entry.lookup_type != "Area" || first_entry.table_name != "Plain") {
        return 4;
    }

    if(first_entry.instruction != "AP(QUESMRK1);LS(DASH,1,CHMGD)") {
        return 5;
    }

    const auto depare_match = std::find_if(
        lookup_catalog->entries.begin(),
        lookup_catalog->entries.end(),
        [](const marine_chart::s52_core_headless::LookupRawEntry& entry) {
            return entry.id == "39" && entry.name == "DEPARE";
        });
    if(depare_match == lookup_catalog->entries.end()) {
        return 6;
    }

    if(depare_match->attribute_codes.size() != 2) {
        return 7;
    }

    if(depare_match->attribute_codes[0].index != 0 || depare_match->attribute_codes[0].code != "DRVAL1?") {
        return 8;
    }

    if(depare_match->attribute_codes[1].index != 1 || depare_match->attribute_codes[1].code != "DRVAL2?") {
        return 9;
    }

    if(depare_match->instruction != "AC(NODTA);AP(PRTSUR01);LS(SOLD,2,CHGRD)") {
        return 10;
    }

    const auto topmar_match = std::find_if(
        lookup_catalog->entries.begin(),
        lookup_catalog->entries.end(),
        [](const marine_chart::s52_core_headless::LookupRawEntry& entry) {
            return entry.id == "1262" && entry.name == "TOPMAR";
        });
    if(topmar_match == lookup_catalog->entries.end()) {
        return 11;
    }

    if(topmar_match->table_name != "Simplified") {
        return 12;
    }

    if(!topmar_match->instruction.empty()) {
        return 13;
    }

    const auto m_accy_match = std::find_if(
        lookup_catalog->entries.begin(),
        lookup_catalog->entries.end(),
        [](const marine_chart::s52_core_headless::LookupRawEntry& entry) {
            return entry.id == "99" && entry.name == "M_ACCY";
        });
    if(m_accy_match == lookup_catalog->entries.end()) {
        return 14;
    }

    if(!m_accy_match->display_category.empty()) {
        return 15;
    }

    const auto achare_count = std::count_if(
        lookup_catalog->entries.begin(),
        lookup_catalog->entries.end(),
        [](const marine_chart::s52_core_headless::LookupRawEntry& entry) {
            return entry.name == "ACHARE";
        });
    if(achare_count < 2) {
        return 16;
    }

    const auto chartsymbols_document =
        marine_chart::s52_core_headless::load_chartsymbols_xml("vendor/opencpn_s57data");
    if(!chartsymbols_document.has_value()) {
        return 15;
    }

    const auto lookup_catalog_from_document =
        marine_chart::s52_core_headless::load_lookup_raw_catalog(*chartsymbols_document);
    if(!lookup_catalog_from_document.has_value()
        || lookup_catalog_from_document->entries.size() != lookup_catalog->entries.size()) {
        return 17;
    }

    return 0;
}
