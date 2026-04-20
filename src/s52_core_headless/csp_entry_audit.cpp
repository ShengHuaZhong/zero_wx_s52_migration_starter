#include "marine_chart/s52_core_headless/csp_entry_audit.h"

namespace marine_chart::s52_core_headless {

NeutralOptional<CspEntryAudit> audit_csp_entries(const LookupRawCatalog& catalog) {
    if(catalog.empty()) {
        return std::nullopt;
    }

    NeutralMap<NeutralString, std::size_t> usage_counts;
    for(const auto& entry : catalog.entries) {
        std::size_t search_offset = 0;
        while(true) {
            const auto csp_begin = entry.instruction.find("CS(", search_offset);
            if(csp_begin == NeutralStringView::npos) {
                break;
            }

            const auto name_begin = csp_begin + 3;
            const auto name_end = entry.instruction.find_first_of(");", name_begin);
            if(name_end == NeutralStringView::npos) {
                return std::nullopt;
            }

            const auto csp_name = make_neutral_string(
                NeutralStringView{entry.instruction}.substr(name_begin, name_end - name_begin));
            if(!csp_name.empty()) {
                ++usage_counts[csp_name];
            }

            search_offset = name_end + 1;
        }
    }

    if(usage_counts.empty()) {
        return std::nullopt;
    }

    CspEntryAudit audit;
    for(const auto& [name, count] : usage_counts) {
        audit.entries.push_back({name, count});
    }

    return audit;
}

NeutralOptional<CspEntryAudit> audit_csp_entries_from_asset_root(NeutralStringView asset_root) {
    const auto catalog = load_lookup_raw_catalog_from_asset_root(asset_root);
    if(!catalog.has_value()) {
        return std::nullopt;
    }

    return audit_csp_entries(*catalog);
}

const CspEntryUsage* find_csp_entry_usage(
    const CspEntryAudit& audit,
    NeutralStringView name) noexcept {
    for(const auto& entry : audit.entries) {
        if(entry.name == name) {
            return &entry;
        }
    }

    return nullptr;
}

}  // namespace marine_chart::s52_core_headless
