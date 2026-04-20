#include "marine_chart/s52_core_headless/symbol_catalog_loader.h"

#include <charconv>

namespace marine_chart::s52_core_headless {
namespace {

[[nodiscard]] NeutralOptional<NeutralString> parse_quoted_attribute(
    NeutralStringView text,
    NeutralStringView marker,
    std::size_t start_offset = 0) {
    const auto marker_offset = text.find(marker, start_offset);
    if(marker_offset == NeutralStringView::npos) {
        return std::nullopt;
    }

    const auto value_begin = marker_offset + marker.size();
    const auto value_end = text.find('"', value_begin);
    if(value_end == NeutralStringView::npos) {
        return std::nullopt;
    }

    return make_neutral_string(text.substr(value_begin, value_end - value_begin));
}

[[nodiscard]] NeutralOptional<int> parse_integer_attribute(
    NeutralStringView text,
    NeutralStringView marker,
    std::size_t start_offset = 0) {
    const auto marker_offset = text.find(marker, start_offset);
    if(marker_offset == NeutralStringView::npos) {
        return std::nullopt;
    }

    const auto value_begin = marker_offset + marker.size();
    const auto value_end = text.find('"', value_begin);
    if(value_end == NeutralStringView::npos) {
        return std::nullopt;
    }

    int value = 0;
    const auto parse_result = std::from_chars(
        text.data() + value_begin,
        text.data() + value_end,
        value);
    if(parse_result.ec != std::errc{}) {
        return std::nullopt;
    }

    return value;
}

[[nodiscard]] NeutralOptional<NeutralString> parse_tag_text(
    NeutralStringView text,
    NeutralStringView begin_tag,
    NeutralStringView end_tag,
    std::size_t start_offset = 0) {
    const auto tag_begin = text.find(begin_tag, start_offset);
    if(tag_begin == NeutralStringView::npos) {
        return std::nullopt;
    }

    const auto value_begin = tag_begin + begin_tag.size();
    const auto value_end = text.find(end_tag, value_begin);
    if(value_end == NeutralStringView::npos) {
        return std::nullopt;
    }

    return make_neutral_string(text.substr(value_begin, value_end - value_begin));
}

}  // namespace

NeutralOptional<SymbolCatalog> load_symbol_catalog(const ChartsymbolsXmlDocument& document) {
    if(!document.valid()) {
        return std::nullopt;
    }

    const auto symbols_begin = document.xml_text.find("<symbols>");
    const auto symbols_end = document.xml_text.find("</symbols>", symbols_begin);
    if(symbols_begin == NeutralStringView::npos || symbols_end == NeutralStringView::npos) {
        return std::nullopt;
    }

    const auto symbols_section = NeutralStringView{document.xml_text}.substr(
        symbols_begin + sizeof("<symbols>") - 1,
        symbols_end - symbols_begin - (sizeof("<symbols>") - 1));

    SymbolCatalog catalog;
    std::size_t symbol_offset = 0;
    while(true) {
        const auto symbol_begin = symbols_section.find("<symbol RCID=\"", symbol_offset);
        if(symbol_begin == NeutralStringView::npos) {
            break;
        }

        const auto symbol_end = symbols_section.find("</symbol>", symbol_begin);
        if(symbol_end == NeutralStringView::npos) {
            return std::nullopt;
        }

        const auto symbol_block = symbols_section.substr(symbol_begin, symbol_end - symbol_begin);
        SymbolDefinition definition;

        const auto rcid = parse_quoted_attribute(symbol_block, "<symbol RCID=\"");
        const auto name = parse_tag_text(symbol_block, "<name>", "</name>");
        const auto description = parse_tag_text(symbol_block, "<description>", "</description>");
        const auto color_reference = parse_tag_text(symbol_block, "<color-ref>", "</color-ref>");
        if(!rcid.has_value() || !name.has_value() || !description.has_value() || !color_reference.has_value()) {
            symbol_offset = symbol_end + sizeof("</symbol>") - 1;
            continue;
        }

        const auto bitmap_begin = symbol_block.find("<bitmap ");
        const auto bitmap_end = symbol_block.find("</bitmap>", bitmap_begin);
        if(bitmap_begin == NeutralStringView::npos || bitmap_end == NeutralStringView::npos) {
            symbol_offset = symbol_end + sizeof("</symbol>") - 1;
            continue;
        }

        const auto bitmap_block = symbol_block.substr(bitmap_begin, bitmap_end - bitmap_begin);
        const auto width = parse_integer_attribute(bitmap_block, "width=\"");
        const auto height = parse_integer_attribute(bitmap_block, "height=\"");
        const auto pivot_x = parse_integer_attribute(bitmap_block, "<pivot x=\"");
        const auto pivot_y = parse_integer_attribute(bitmap_block, "y=\"", bitmap_block.find("<pivot x=\""));
        const auto graphics_x = parse_integer_attribute(bitmap_block, "<graphics-location x=\"");
        const auto graphics_y = parse_integer_attribute(
            bitmap_block,
            "y=\"",
            bitmap_block.find("<graphics-location x=\""));
        if(!width.has_value()
            || !height.has_value()
            || !pivot_x.has_value()
            || !pivot_y.has_value()
            || !graphics_x.has_value()
            || !graphics_y.has_value()) {
            symbol_offset = symbol_end + sizeof("</symbol>") - 1;
            continue;
        }

        definition.rcid = *rcid;
        definition.name = *name;
        definition.description = *description;
        definition.source_rect = make_neutral_rect(*graphics_x, *graphics_y, *width, *height);
        definition.pivot = make_neutral_point(*pivot_x, *pivot_y);
        definition.color_reference = *color_reference;

        if(definition.empty()) {
            symbol_offset = symbol_end + sizeof("</symbol>") - 1;
            continue;
        }

        catalog.symbols.emplace(definition.name, definition);
        symbol_offset = symbol_end + sizeof("</symbol>") - 1;
    }

    if(catalog.empty()) {
        return std::nullopt;
    }

    return catalog;
}

NeutralOptional<SymbolCatalog> load_symbol_catalog_from_asset_root(NeutralStringView asset_root) {
    const auto document = load_chartsymbols_xml(asset_root);
    if(!document.has_value()) {
        return std::nullopt;
    }

    return load_symbol_catalog(*document);
}

}  // namespace marine_chart::s52_core_headless
