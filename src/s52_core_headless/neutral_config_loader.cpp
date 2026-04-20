#include "marine_chart/s52_core_headless/neutral_config_loader.h"

namespace marine_chart::s52_core_headless {
namespace {

[[nodiscard]] NeutralStringView trim_view(NeutralStringView text) noexcept {
    auto begin = text.find_first_not_of(" \t\r");
    if(begin == NeutralStringView::npos) {
        return {};
    }

    const auto end = text.find_last_not_of(" \t\r");
    return text.substr(begin, end - begin + 1);
}

}  // namespace

NeutralConfigDocument load_neutral_config_from_text(NeutralStringView text) {
    NeutralConfigDocument document;

    std::size_t line_begin = 0;
    while(line_begin <= text.size()) {
        const auto line_end = text.find('\n', line_begin);
        const auto raw_line = text.substr(
            line_begin,
            line_end == NeutralStringView::npos ? text.size() - line_begin : line_end - line_begin);
        const auto line = trim_view(raw_line);

        if(!line.empty() && !line.starts_with('#') && !line.starts_with(';')) {
            const auto separator = line.find('=');
            if(separator != NeutralStringView::npos) {
                const auto key = trim_view(line.substr(0, separator));
                const auto value = trim_view(line.substr(separator + 1));
                if(!key.empty()) {
                    document.values[make_neutral_string(key)] = make_neutral_string(value);
                }
            }
        }

        if(line_end == NeutralStringView::npos) {
            break;
        }

        line_begin = line_end + 1;
    }

    return document;
}

NeutralOptional<NeutralString> find_config_value(
    const NeutralConfigDocument& document,
    NeutralStringView key) {
    const auto match = document.values.find(make_neutral_string(key));
    if(match == document.values.end()) {
        return std::nullopt;
    }

    return match->second;
}

}  // namespace marine_chart::s52_core_headless
