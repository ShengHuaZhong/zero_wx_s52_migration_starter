#include "marine_chart/s52_core_headless/pattern_catalog_loader.h"

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

NeutralOptional<PatternCatalog> load_pattern_catalog(const ChartsymbolsXmlDocument& document) {
    if(!document.valid()) {
        return std::nullopt;
    }

    const auto section_begin = document.xml_text.find("<patterns>");
    const auto section_end = document.xml_text.find("</patterns>", section_begin);
    if(section_begin == NeutralStringView::npos || section_end == NeutralStringView::npos) {
        return std::nullopt;
    }

    const auto section = NeutralStringView{document.xml_text}.substr(
        section_begin + sizeof("<patterns>") - 1,
        section_end - section_begin - (sizeof("<patterns>") - 1));

    PatternCatalog catalog;
    std::size_t pattern_offset = 0;
    while(true) {
        const auto pattern_begin = section.find("<pattern RCID=\"", pattern_offset);
        if(pattern_begin == NeutralStringView::npos) {
            break;
        }

        const auto pattern_end = section.find("</pattern>", pattern_begin);
        if(pattern_end == NeutralStringView::npos) {
            return std::nullopt;
        }

        const auto pattern_block = section.substr(pattern_begin, pattern_end - pattern_begin);
        PatternDefinition definition;

        const auto rcid = parse_quoted_attribute(pattern_block, "<pattern RCID=\"");
        const auto name = parse_tag_text(pattern_block, "<name>", "</name>");
        const auto definition_code = parse_tag_text(pattern_block, "<definition>", "</definition>");
        const auto fill_type = parse_tag_text(pattern_block, "<filltype>", "</filltype>");
        const auto spacing = parse_tag_text(pattern_block, "<spacing>", "</spacing>");
        const auto description = parse_tag_text(pattern_block, "<description>", "</description>");
        const auto hpgl = parse_tag_text(pattern_block, "<HPGL>", "</HPGL>");
        const auto color_reference = parse_tag_text(pattern_block, "<color-ref>", "</color-ref>");
        if(!rcid.has_value()
            || !name.has_value()
            || !definition_code.has_value()
            || !fill_type.has_value()
            || !spacing.has_value()
            || !description.has_value()
            || !hpgl.has_value()
            || !color_reference.has_value()) {
            pattern_offset = pattern_end + sizeof("</pattern>") - 1;
            continue;
        }

        const auto vector_begin = pattern_block.find("<vector ");
        const auto vector_end = pattern_block.find("</vector>", vector_begin);
        if(vector_begin == NeutralStringView::npos || vector_end == NeutralStringView::npos) {
            pattern_offset = pattern_end + sizeof("</pattern>") - 1;
            continue;
        }

        const auto vector_block = pattern_block.substr(vector_begin, vector_end - vector_begin);
        const auto width = parse_integer_attribute(vector_block, "width=\"");
        const auto height = parse_integer_attribute(vector_block, "height=\"");
        const auto pivot_x = parse_integer_attribute(vector_block, "<pivot x=\"");
        const auto pivot_y = parse_integer_attribute(vector_block, "y=\"", vector_block.find("<pivot x=\""));
        const auto origin_x = parse_integer_attribute(vector_block, "<origin x=\"");
        const auto origin_y = parse_integer_attribute(vector_block, "y=\"", vector_block.find("<origin x=\""));
        if(!width.has_value()
            || !height.has_value()
            || !pivot_x.has_value()
            || !pivot_y.has_value()
            || !origin_x.has_value()
            || !origin_y.has_value()) {
            pattern_offset = pattern_end + sizeof("</pattern>") - 1;
            continue;
        }

        definition.rcid = *rcid;
        definition.name = *name;
        definition.definition_code = *definition_code;
        definition.fill_type = *fill_type;
        definition.spacing = *spacing;
        definition.tile_size = make_neutral_size(*width, *height);
        definition.pivot = make_neutral_point(*pivot_x, *pivot_y);
        definition.origin = make_neutral_point(*origin_x, *origin_y);
        definition.description = *description;
        definition.color_reference = *color_reference;
        definition.pattern_source = *hpgl;

        if(definition.empty()) {
            pattern_offset = pattern_end + sizeof("</pattern>") - 1;
            continue;
        }

        catalog.patterns.emplace(definition.name, definition);
        pattern_offset = pattern_end + sizeof("</pattern>") - 1;
    }

    if(catalog.empty()) {
        return std::nullopt;
    }

    return catalog;
}

NeutralOptional<PatternCatalog> load_pattern_catalog_from_asset_root(NeutralStringView asset_root) {
    const auto document = load_chartsymbols_xml(asset_root);
    if(!document.has_value()) {
        return std::nullopt;
    }

    return load_pattern_catalog(*document);
}

}  // namespace marine_chart::s52_core_headless
