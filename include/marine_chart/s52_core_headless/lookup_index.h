#pragma once

#include "marine_chart/s52_core_headless/lookup_raw_loader.h"
#include "marine_chart/s52_core_headless/neutral_containers.h"
#include "marine_chart/s52_core_headless/neutral_string.h"

namespace marine_chart::s52_core_headless {

struct LookupIndexBucket final {
    NeutralString object_class;
    NeutralString lookup_type;
    NeutralString table_name;
    NeutralVector<LookupRawEntry> entries;

    [[nodiscard]] bool empty() const noexcept {
        return object_class.empty()
            || lookup_type.empty()
            || table_name.empty()
            || entries.empty();
    }

    bool operator==(const LookupIndexBucket&) const noexcept = default;
};

struct LookupIndex final {
    NeutralMap<NeutralString, LookupIndexBucket> buckets;

    [[nodiscard]] bool empty() const noexcept {
        return buckets.empty();
    }

    bool operator==(const LookupIndex&) const noexcept = default;
};

[[nodiscard]] NeutralString compose_lookup_index_key(
    NeutralStringView object_class,
    NeutralStringView lookup_type,
    NeutralStringView table_name);

[[nodiscard]] NeutralOptional<LookupIndex> build_lookup_index(const LookupRawCatalog& catalog);

[[nodiscard]] NeutralOptional<LookupIndex> build_lookup_index_from_asset_root(
    NeutralStringView asset_root);

[[nodiscard]] const LookupIndexBucket* find_lookup_index_bucket(
    const LookupIndex& index,
    NeutralStringView object_class,
    NeutralStringView lookup_type,
    NeutralStringView table_name) noexcept;

}  // namespace marine_chart::s52_core_headless
