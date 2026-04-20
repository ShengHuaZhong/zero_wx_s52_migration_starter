#pragma once

#include "marine_chart/s52_core_headless/chartsymbols_xml_loader.h"
#include "marine_chart/s52_core_headless/neutral_containers.h"
#include "marine_chart/s52_core_headless/neutral_string.h"

namespace marine_chart::s52_core_headless {

struct LookupAttributeCode final {
    int index{-1};
    NeutralString code;

    [[nodiscard]] bool empty() const noexcept {
        return index < 0 || code.empty();
    }

    bool operator==(const LookupAttributeCode&) const noexcept = default;
};

struct LookupRawEntry final {
    NeutralString id;
    NeutralString rcid;
    NeutralString name;
    NeutralString lookup_type;
    NeutralString display_priority;
    NeutralString radar_priority;
    NeutralString table_name;
    NeutralVector<LookupAttributeCode> attribute_codes;
    NeutralString instruction;
    NeutralString display_category;
    NeutralString comment;

    [[nodiscard]] bool empty() const noexcept {
        return id.empty()
            || rcid.empty()
            || name.empty()
            || lookup_type.empty()
            || display_priority.empty()
            || radar_priority.empty()
            || table_name.empty();
    }

    bool operator==(const LookupRawEntry&) const noexcept = default;
};

struct LookupRawCatalog final {
    NeutralVector<LookupRawEntry> entries;

    [[nodiscard]] bool empty() const noexcept {
        return entries.empty();
    }

    bool operator==(const LookupRawCatalog&) const noexcept = default;
};

[[nodiscard]] NeutralOptional<LookupRawCatalog> load_lookup_raw_catalog(
    const ChartsymbolsXmlDocument& document);

[[nodiscard]] NeutralOptional<LookupRawCatalog> load_lookup_raw_catalog_from_asset_root(
    NeutralStringView asset_root);

}  // namespace marine_chart::s52_core_headless
