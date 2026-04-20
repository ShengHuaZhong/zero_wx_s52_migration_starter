#include "marine_chart/s52_core_headless/chartsymbols_xml_loader.h"

#include <filesystem>
#include <fstream>
#include <sstream>

namespace marine_chart::s52_core_headless {
namespace {

[[nodiscard]] bool contains_marker(NeutralStringView text, NeutralStringView marker) noexcept {
    return text.find(marker) != NeutralStringView::npos;
}

}  // namespace

NeutralString chartsymbols_xml_path_from_asset_root(NeutralStringView asset_root) {
    const auto path = std::filesystem::path{make_neutral_string(asset_root)} / "chartsymbols.xml";
    return make_neutral_string(path.generic_string());
}

NeutralOptional<ChartsymbolsXmlDocument> load_chartsymbols_xml(NeutralStringView asset_root) {
    const auto xml_path = chartsymbols_xml_path_from_asset_root(asset_root);
    std::ifstream input_stream{xml_path, std::ios::binary};
    if(!input_stream.is_open()) {
        return std::nullopt;
    }

    std::ostringstream buffer;
    buffer << input_stream.rdbuf();
    const auto xml_text = make_neutral_string(buffer.str());
    if(xml_text.empty()) {
        return std::nullopt;
    }

    ChartsymbolsXmlDocument document;
    document.source_path = xml_path;
    document.xml_text = xml_text;
    document.has_color_tables = contains_marker(xml_text, "<color-tables>");
    document.has_line_styles = contains_marker(xml_text, "<line-styles>");
    document.has_patterns = contains_marker(xml_text, "<patterns>");
    document.has_symbols = contains_marker(xml_text, "<symbols>");

    if(!contains_marker(xml_text, "<chartsymbols>") || !document.valid()) {
        return std::nullopt;
    }

    return document;
}

}  // namespace marine_chart::s52_core_headless
