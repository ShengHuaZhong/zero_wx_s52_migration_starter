#pragma once

#include "marine_chart/s52_core_headless/lookup_raw_loader.h"
#include "marine_chart/s52_core_headless/neutral_containers.h"
#include "marine_chart/s52_core_headless/neutral_string.h"

#include <cstddef>

namespace marine_chart::s52_core_headless {

struct CspEntryUsage final {
    NeutralString name;
    std::size_t count{0};

    [[nodiscard]] bool empty() const noexcept {
        return name.empty() || count == 0;
    }

    bool operator==(const CspEntryUsage&) const noexcept = default;
};

struct CspEntryAudit final {
    NeutralVector<CspEntryUsage> entries;

    [[nodiscard]] bool empty() const noexcept {
        return entries.empty();
    }

    bool operator==(const CspEntryAudit&) const noexcept = default;
};

[[nodiscard]] NeutralOptional<CspEntryAudit> audit_csp_entries(const LookupRawCatalog& catalog);

[[nodiscard]] NeutralOptional<CspEntryAudit> audit_csp_entries_from_asset_root(
    NeutralStringView asset_root);

[[nodiscard]] const CspEntryUsage* find_csp_entry_usage(
    const CspEntryAudit& audit,
    NeutralStringView name) noexcept;

}  // namespace marine_chart::s52_core_headless
