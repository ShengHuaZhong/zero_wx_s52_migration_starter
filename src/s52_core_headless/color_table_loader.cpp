#include "marine_chart/s52_core_headless/color_table_loader.h"

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

}  // namespace

NeutralOptional<PaletteCatalog> load_color_table_catalog(const ChartsymbolsXmlDocument& document) {
    if(!document.valid()) {
        return std::nullopt;
    }

    PaletteCatalog catalog;

    std::size_t table_offset = 0;
    while(true) {
        const auto table_begin = document.xml_text.find("<color-table name=\"", table_offset);
        if(table_begin == NeutralStringView::npos) {
            break;
        }

        const auto block_begin = document.xml_text.find('>', table_begin);
        const auto block_end = document.xml_text.find("</color-table>", block_begin);
        if(block_begin == NeutralStringView::npos || block_end == NeutralStringView::npos) {
            return std::nullopt;
        }

        PaletteDefinition palette;
        const auto palette_name = parse_quoted_attribute(document.xml_text, "<color-table name=\"", table_begin);
        if(!palette_name.has_value()) {
            return std::nullopt;
        }

        palette.name = *palette_name;

        const auto block = NeutralStringView{document.xml_text}.substr(block_begin + 1, block_end - block_begin - 1);
        const auto graphics_file = parse_quoted_attribute(block, "<graphics-file name=\"");
        if(!graphics_file.has_value()) {
            return std::nullopt;
        }

        palette.graphics_file_name = *graphics_file;

        std::size_t color_offset = 0;
        while(true) {
            const auto color_begin = block.find("<color name=\"", color_offset);
            if(color_begin == NeutralStringView::npos) {
                break;
            }

            const auto color_end = block.find("/>", color_begin);
            if(color_end == NeutralStringView::npos) {
                return std::nullopt;
            }

            const auto color_fragment = block.substr(color_begin, color_end - color_begin);
            const auto color_name = parse_quoted_attribute(color_fragment, "<color name=\"");
            const auto red = parse_integer_attribute(color_fragment, "r=\"");
            const auto green = parse_integer_attribute(color_fragment, "g=\"");
            const auto blue = parse_integer_attribute(color_fragment, "b=\"");
            if(!color_name.has_value() || !red.has_value() || !green.has_value() || !blue.has_value()) {
                return std::nullopt;
            }

            palette.entries.emplace(
                *color_name,
                make_neutral_color(
                    static_cast<std::uint8_t>(*red),
                    static_cast<std::uint8_t>(*green),
                    static_cast<std::uint8_t>(*blue)));

            color_offset = color_end + 2;
        }

        if(palette.empty()) {
            return std::nullopt;
        }

        catalog.palettes.emplace(palette.name, palette);
        table_offset = block_end + sizeof("</color-table>") - 1;
    }

    if(catalog.empty()) {
        return std::nullopt;
    }

    return catalog;
}

NeutralOptional<PaletteCatalog> load_color_table_catalog_from_asset_root(NeutralStringView asset_root) {
    const auto document = load_chartsymbols_xml(asset_root);
    if(!document.has_value()) {
        return std::nullopt;
    }

    return load_color_table_catalog(*document);
}

}  // namespace marine_chart::s52_core_headless
