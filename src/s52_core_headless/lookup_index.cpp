#include "marine_chart/s52_core_headless/lookup_index.h"

namespace marine_chart::s52_core_headless {

NeutralString compose_lookup_index_key(
    NeutralStringView object_class,
    NeutralStringView lookup_type,
    NeutralStringView table_name) {
    if(object_class.empty() || lookup_type.empty() || table_name.empty()) {
        return {};
    }

    NeutralString key;
    key.reserve(object_class.size() + lookup_type.size() + table_name.size() + 2);
    key.append(object_class);
    key.push_back('\x1f');
    key.append(lookup_type);
    key.push_back('\x1f');
    key.append(table_name);
    return key;
}

NeutralOptional<LookupIndex> build_lookup_index(const LookupRawCatalog& catalog) {
    if(catalog.empty()) {
        return std::nullopt;
    }

    LookupIndex index;
    for(const auto& entry : catalog.entries) {
        if(entry.empty()) {
            continue;
        }

        const auto key = compose_lookup_index_key(entry.name, entry.lookup_type, entry.table_name);
        if(key.empty()) {
            continue;
        }

        auto bucket_match = index.buckets.find(key);
        if(bucket_match == index.buckets.end()) {
            LookupIndexBucket bucket;
            bucket.object_class = entry.name;
            bucket.lookup_type = entry.lookup_type;
            bucket.table_name = entry.table_name;
            bucket.entries.push_back(entry);
            index.buckets.emplace(key, bucket);
            continue;
        }

        bucket_match->second.entries.push_back(entry);
    }

    if(index.empty()) {
        return std::nullopt;
    }

    return index;
}

NeutralOptional<LookupIndex> build_lookup_index_from_asset_root(NeutralStringView asset_root) {
    const auto catalog = load_lookup_raw_catalog_from_asset_root(asset_root);
    if(!catalog.has_value()) {
        return std::nullopt;
    }

    return build_lookup_index(*catalog);
}

const LookupIndexBucket* find_lookup_index_bucket(
    const LookupIndex& index,
    NeutralStringView object_class,
    NeutralStringView lookup_type,
    NeutralStringView table_name) noexcept {
    const auto key = compose_lookup_index_key(object_class, lookup_type, table_name);
    if(key.empty()) {
        return nullptr;
    }

    const auto match = index.buckets.find(key);
    if(match == index.buckets.end()) {
        return nullptr;
    }

    return &match->second;
}

}  // namespace marine_chart::s52_core_headless
