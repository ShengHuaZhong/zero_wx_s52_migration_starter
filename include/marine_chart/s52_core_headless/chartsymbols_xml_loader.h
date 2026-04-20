#pragma once

#include "marine_chart/s52_core_headless/neutral_containers.h"
#include "marine_chart/s52_core_headless/neutral_string.h"

namespace marine_chart::s52_core_headless {

struct ChartsymbolsXmlDocument final {
    NeutralString source_path;
    NeutralString xml_text;
    bool has_color_tables{false};
    bool has_line_styles{false};
    bool has_patterns{false};
    bool has_symbols{false};

    [[nodiscard]] bool valid() const noexcept {
        return !source_path.empty()
            && !xml_text.empty()
            && has_color_tables
            && has_line_styles
            && has_patterns
            && has_symbols;
    }
};

[[nodiscard]] NeutralString chartsymbols_xml_path_from_asset_root(NeutralStringView asset_root);

[[nodiscard]] NeutralOptional<ChartsymbolsXmlDocument> load_chartsymbols_xml(
    NeutralStringView asset_root);

}  // namespace marine_chart::s52_core_headless
