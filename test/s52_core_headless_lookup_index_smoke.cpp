#include "marine_chart/s52_core_headless/lookup_index.h"

#include <algorithm>

int main() {
    const auto raw_catalog =
        marine_chart::s52_core_headless::load_lookup_raw_catalog_from_asset_root("vendor/opencpn_s57data");
    if(!raw_catalog.has_value() || raw_catalog->empty()) {
        return 1;
    }

    const auto index = marine_chart::s52_core_headless::build_lookup_index(*raw_catalog);
    if(!index.has_value() || index->empty()) {
        return 2;
    }

    std::size_t indexed_entry_count = 0;
    for(const auto& [key, bucket] : index->buckets) {
        if(key.empty() || bucket.empty()) {
            return 3;
        }

        indexed_entry_count += bucket.entries.size();
    }

    if(indexed_entry_count != raw_catalog->entries.size()) {
        return 4;
    }

    const auto* achare_plain = marine_chart::s52_core_headless::find_lookup_index_bucket(
        *index,
        "ACHARE",
        "Area",
        "Plain");
    if(achare_plain == nullptr || achare_plain->entries.size() != 3) {
        return 5;
    }

    if(achare_plain->entries[0].id != "1" || achare_plain->entries[1].id != "2") {
        return 6;
    }

    const auto duplicate_id_2_count = std::count_if(
        achare_plain->entries.begin(),
        achare_plain->entries.end(),
        [](const marine_chart::s52_core_headless::LookupRawEntry& entry) {
            return entry.id == "2";
        });
    if(duplicate_id_2_count != 2) {
        return 7;
    }

    const auto* topmar_simplified = marine_chart::s52_core_headless::find_lookup_index_bucket(
        *index,
        "TOPMAR",
        "Point",
        "Simplified");
    if(topmar_simplified == nullptr) {
        return 8;
    }

    if(std::none_of(
           topmar_simplified->entries.begin(),
           topmar_simplified->entries.end(),
           [](const marine_chart::s52_core_headless::LookupRawEntry& entry) {
               return entry.id == "1262";
           })) {
        return 9;
    }

    const auto* topmar_paper = marine_chart::s52_core_headless::find_lookup_index_bucket(
        *index,
        "TOPMAR",
        "Point",
        "Paper");
    if(topmar_paper == nullptr) {
        return 10;
    }

    if(std::none_of(
           topmar_paper->entries.begin(),
           topmar_paper->entries.end(),
           [](const marine_chart::s52_core_headless::LookupRawEntry& entry) {
               return entry.id == "12701";
           })) {
        return 11;
    }

    if(marine_chart::s52_core_headless::find_lookup_index_bucket(
           *index,
           "NOTREAL",
           "Point",
           "Plain")
        != nullptr) {
        return 12;
    }

    const auto index_from_asset_root =
        marine_chart::s52_core_headless::build_lookup_index_from_asset_root("vendor/opencpn_s57data");
    if(!index_from_asset_root.has_value()
        || index_from_asset_root->buckets.size() != index->buckets.size()) {
        return 13;
    }

    return 0;
}
