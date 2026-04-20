#include "marine_chart/s52_core_headless/lookup_raw_loader.h"

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

[[nodiscard]] NeutralOptional<NeutralVector<LookupAttributeCode>> parse_attribute_codes(
    NeutralStringView lookup_block) {
    NeutralVector<LookupAttributeCode> attribute_codes;

    std::size_t attribute_offset = 0;
    while(true) {
        const auto attribute_begin = lookup_block.find("<attrib-code index=\"", attribute_offset);
        if(attribute_begin == NeutralStringView::npos) {
            break;
        }

        const auto attribute_end = lookup_block.find("</attrib-code>", attribute_begin);
        if(attribute_end == NeutralStringView::npos) {
            return std::nullopt;
        }

        const auto attribute_block = lookup_block.substr(attribute_begin, attribute_end - attribute_begin);
        const auto index = parse_integer_attribute(attribute_block, "<attrib-code index=\"");
        if(!index.has_value()) {
            attribute_offset = attribute_end + sizeof("</attrib-code>") - 1;
            continue;
        }

        const auto value_begin = attribute_block.find('>');
        if(value_begin == NeutralStringView::npos) {
            return std::nullopt;
        }

        LookupAttributeCode attribute_code;
        attribute_code.index = *index;
        attribute_code.code = make_neutral_string(attribute_block.substr(value_begin + 1));
        if(!attribute_code.empty()) {
            attribute_codes.push_back(attribute_code);
        }

        attribute_offset = attribute_end + sizeof("</attrib-code>") - 1;
    }

    return attribute_codes;
}

}  // namespace

NeutralOptional<LookupRawCatalog> load_lookup_raw_catalog(const ChartsymbolsXmlDocument& document) {
    if(!document.valid()) {
        return std::nullopt;
    }

    const auto section_begin = document.xml_text.find("<lookups>");
    const auto section_end = document.xml_text.find("</lookups>", section_begin);
    if(section_begin == NeutralStringView::npos || section_end == NeutralStringView::npos) {
        return std::nullopt;
    }

    const auto section = NeutralStringView{document.xml_text}.substr(
        section_begin + sizeof("<lookups>") - 1,
        section_end - section_begin - (sizeof("<lookups>") - 1));

    LookupRawCatalog catalog;
    std::size_t lookup_offset = 0;
    while(true) {
        const auto lookup_begin = section.find("<lookup id=\"", lookup_offset);
        if(lookup_begin == NeutralStringView::npos) {
            break;
        }

        const auto lookup_end = section.find("</lookup>", lookup_begin);
        if(lookup_end == NeutralStringView::npos) {
            return std::nullopt;
        }

        const auto lookup_block = section.substr(lookup_begin, lookup_end - lookup_begin);
        const auto lookup_open_tag_end = lookup_block.find('>');
        if(lookup_open_tag_end == NeutralStringView::npos) {
            return std::nullopt;
        }

        const auto lookup_open_tag = lookup_block.substr(0, lookup_open_tag_end);

        LookupRawEntry entry;
        entry.id = parse_quoted_attribute(lookup_open_tag, "<lookup id=\"").value_or("");
        entry.rcid = parse_quoted_attribute(lookup_open_tag, "RCID=\"").value_or("");
        entry.name = parse_quoted_attribute(lookup_open_tag, "name=\"").value_or("");
        entry.lookup_type = parse_tag_text(lookup_block, "<type>", "</type>").value_or("");
        entry.display_priority = parse_tag_text(lookup_block, "<disp-prio>", "</disp-prio>").value_or("");
        entry.radar_priority = parse_tag_text(lookup_block, "<radar-prio>", "</radar-prio>").value_or("");
        entry.table_name = parse_tag_text(lookup_block, "<table-name>", "</table-name>").value_or("");
        entry.instruction = parse_tag_text(lookup_block, "<instruction>", "</instruction>").value_or("");
        entry.display_category = parse_tag_text(lookup_block, "<display-cat>", "</display-cat>").value_or("");
        entry.comment = parse_tag_text(lookup_block, "<comment>", "</comment>").value_or("");

        const auto attribute_codes = parse_attribute_codes(lookup_block);
        if(!attribute_codes.has_value()) {
            return std::nullopt;
        }

        entry.attribute_codes = *attribute_codes;

        if(!entry.empty()) {
            catalog.entries.push_back(entry);
        }

        lookup_offset = lookup_end + sizeof("</lookup>") - 1;
    }

    if(catalog.empty()) {
        return std::nullopt;
    }

    return catalog;
}

NeutralOptional<LookupRawCatalog> load_lookup_raw_catalog_from_asset_root(NeutralStringView asset_root) {
    const auto document = load_chartsymbols_xml(asset_root);
    if(!document.has_value()) {
        return std::nullopt;
    }

    return load_lookup_raw_catalog(*document);
}

}  // namespace marine_chart::s52_core_headless
