#pragma once

#include "marine_chart/s52_core_headless/asset_catalog_types.h"
#include "marine_chart/s52_core_headless/chartsymbols_xml_loader.h"
#include "marine_chart/s52_core_headless/neutral_containers.h"

namespace marine_chart::s52_core_headless {

[[nodiscard]] NeutralOptional<LineStyleCatalog> load_line_style_catalog(
    const ChartsymbolsXmlDocument& document);

[[nodiscard]] NeutralOptional<LineStyleCatalog> load_line_style_catalog_from_asset_root(
    NeutralStringView asset_root);

}  // namespace marine_chart::s52_core_headless
