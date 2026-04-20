#include "marine_chart/s52_core_headless/headless_core_init.h"

#include "marine_chart/s52_core_headless/color_table_loader.h"
#include "marine_chart/s52_core_headless/line_style_loader.h"
#include "marine_chart/s52_core_headless/pattern_catalog_loader.h"
#include "marine_chart/s52_core_headless/symbol_catalog_loader.h"

#include <cstdlib>
#include <filesystem>

namespace marine_chart::s52_core_headless {
namespace {

[[nodiscard]] NeutralOptional<NeutralString> resolve_asset_root(
    NeutralStringView requested_asset_root) {
    if(!requested_asset_root.empty()) {
        const auto requested_path = std::filesystem::path{make_neutral_string(requested_asset_root)};
        if(std::filesystem::is_directory(requested_path)) {
            return make_neutral_string(requested_path.generic_string());
        }
    }

    if(const char* environment_root = std::getenv("S52_ASSET_ROOT");
        environment_root != nullptr && environment_root[0] != '\0') {
        const auto environment_path = std::filesystem::path{environment_root};
        if(std::filesystem::is_directory(environment_path)) {
            return make_neutral_string(environment_path.generic_string());
        }
    }

    const auto repo_fallback = std::filesystem::path{"vendor"} / "opencpn_s57data";
    if(std::filesystem::is_directory(repo_fallback)) {
        return make_neutral_string(repo_fallback.generic_string());
    }

    return std::nullopt;
}

}  // namespace

NeutralOptional<HeadlessCoreInitialization> initialize_headless_core(
    NeutralStringView requested_asset_root) {
    const auto resolved_asset_root = resolve_asset_root(requested_asset_root);
    if(!resolved_asset_root.has_value()) {
        return std::nullopt;
    }

    const auto chartsymbols_document = load_chartsymbols_xml(*resolved_asset_root);
    if(!chartsymbols_document.has_value()) {
        return std::nullopt;
    }

    const auto attribute_dictionary = load_attribute_dictionary(*resolved_asset_root);
    const auto object_class_dictionary = load_object_class_dictionary(*resolved_asset_root);
    const auto palettes = load_color_table_catalog(*chartsymbols_document);
    const auto symbols = load_symbol_catalog(*chartsymbols_document);
    const auto line_styles = load_line_style_catalog(*chartsymbols_document);
    const auto patterns = load_pattern_catalog(*chartsymbols_document);

    if(!attribute_dictionary.has_value()
        || !object_class_dictionary.has_value()
        || !palettes.has_value()
        || !symbols.has_value()
        || !line_styles.has_value()
        || !patterns.has_value()) {
        return std::nullopt;
    }

    HeadlessCoreInitialization initialization;
    initialization.asset_root = *resolved_asset_root;
    initialization.chartsymbols_document = *chartsymbols_document;
    initialization.attribute_dictionary = *attribute_dictionary;
    initialization.object_class_dictionary = *object_class_dictionary;
    initialization.asset_catalogs.palettes = *palettes;
    initialization.asset_catalogs.symbols = *symbols;
    initialization.asset_catalogs.line_styles = *line_styles;
    initialization.asset_catalogs.patterns = *patterns;

    if(!initialization.valid()) {
        return std::nullopt;
    }

    return initialization;
}

}  // namespace marine_chart::s52_core_headless
