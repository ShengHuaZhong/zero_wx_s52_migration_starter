#include "marine_chart/s52_core_headless/portrayal_ir_pipeline.h"

#include "marine_chart/s52_core_headless/area_portrayal_selection.h"
#include "marine_chart/s52_core_headless/line_portrayal_selection.h"
#include "marine_chart/s52_core_headless/point_portrayal_selection.h"
#include "marine_chart/s52_core_headless/text_rule_selection.h"

#include <string>

namespace marine_chart::s52_core_headless {
namespace {

[[nodiscard]] chart_runtime::PrimitiveKind to_runtime_primitive(FeaturePrimitiveType primitive_type) noexcept {
    switch(primitive_type) {
    case FeaturePrimitiveType::point:
        return chart_runtime::PrimitiveKind::point;
    case FeaturePrimitiveType::line:
        return chart_runtime::PrimitiveKind::line;
    case FeaturePrimitiveType::area:
        return chart_runtime::PrimitiveKind::area;
    case FeaturePrimitiveType::unknown:
    default:
        return chart_runtime::PrimitiveKind::unknown;
    }
}

[[nodiscard]] chart_runtime::InstructionSource make_instruction_source(
    const LookupKey& lookup_key,
    const LookupRawEntry& lookup_entry) {
    chart_runtime::InstructionSource source;
    source.object_class = lookup_key.object_class;
    source.lookup_type = lookup_key.lookup_type;
    source.table_name = lookup_key.table_name;
    source.lookup_id = lookup_entry.id;
    source.raw_instruction = lookup_entry.instruction;
    return source;
}

[[nodiscard]] std::string make_stable_instruction_id(
    std::string_view prefix,
    const LookupKey& lookup_key,
    const LookupRawEntry& lookup_entry,
    std::size_t index = 0,
    bool include_index = false) {
    auto stable_id = std::string{prefix};
    stable_id += ":";
    stable_id += lookup_key.object_class;
    stable_id += ":";
    stable_id += lookup_entry.id;
    if(include_index) {
        stable_id += ":";
        stable_id += std::to_string(index);
    }
    return stable_id;
}

[[nodiscard]] chart_runtime::InstructionIR make_instruction_ir(
    chart_runtime::InstructionKind kind,
    FeaturePrimitiveType primitive_type,
    std::string_view stable_id_prefix,
    const LookupKey& lookup_key,
    const LookupRawEntry& lookup_entry,
    std::size_t index = 0,
    bool include_index = false) {
    chart_runtime::InstructionIR instruction;
    instruction.kind = kind;
    instruction.primitive = to_runtime_primitive(primitive_type);
    instruction.stable_id = make_stable_instruction_id(stable_id_prefix, lookup_key, lookup_entry, index, include_index);
    instruction.source = make_instruction_source(lookup_key, lookup_entry);
    return instruction;
}

[[nodiscard]] chart_runtime::TextRuleKind to_runtime_text_rule_kind(TextRuleInstructionKind rule_kind) noexcept {
    switch(rule_kind) {
    case TextRuleInstructionKind::tx:
        return chart_runtime::TextRuleKind::tx;
    case TextRuleInstructionKind::te:
        return chart_runtime::TextRuleKind::te;
    default:
        return chart_runtime::TextRuleKind::unknown;
    }
}

[[nodiscard]] chart_runtime::DisplayPriorityGroup to_runtime_display_priority_group(
    s52_core_headless::DisplayPriorityGroup group) noexcept {
    using Source = s52_core_headless::DisplayPriorityGroup;
    using Target = chart_runtime::DisplayPriorityGroup;

    switch(group) {
    case Source::no_data:
        return Target::no_data;
    case Source::group_1:
        return Target::group_1;
    case Source::area_1:
        return Target::area_1;
    case Source::area_2:
        return Target::area_2;
    case Source::point_symbol:
        return Target::point_symbol;
    case Source::line_symbol:
        return Target::line_symbol;
    case Source::area_symbol:
        return Target::area_symbol;
    case Source::routing:
        return Target::routing;
    case Source::hazards:
        return Target::hazards;
    case Source::mariners:
        return Target::mariners;
    case Source::unknown:
    default:
        return Target::unknown;
    }
}

}  // namespace

chart_runtime::FeaturePortrayalIR build_feature_portrayal_ir(
    const LookupIndex& lookup_index,
    const RuleLayerFeature& feature,
    const MarinerSettings& mariner_settings) {
    chart_runtime::FeaturePortrayalIR portrayal_ir;

    if(const auto point_selection = select_point_portrayal(lookup_index, feature, mariner_settings);
       point_selection.has_value() && !point_selection->symbol_name.empty()) {
        chart_runtime::PointSymbolIR point_symbol_ir;
        point_symbol_ir.instruction = make_instruction_ir(
            chart_runtime::InstructionKind::point_symbol,
            feature.primitive_type,
            "point-symbol",
            point_selection->lookup_key,
            point_selection->lookup_entry);
        point_symbol_ir.symbol_name = point_selection->symbol_name;
        if(point_symbol_ir.valid()) {
            portrayal_ir.point_symbols.push_back(point_symbol_ir);
        }
    }

    if(const auto line_selection = select_line_portrayal(lookup_index, feature, mariner_settings);
       line_selection.has_value() && !line_selection->line_style_name.empty()) {
        chart_runtime::LineStyleIR line_style_ir;
        line_style_ir.instruction = make_instruction_ir(
            chart_runtime::InstructionKind::line_style,
            feature.primitive_type,
            "line-style",
            line_selection->lookup_key,
            line_selection->lookup_entry);
        line_style_ir.line_style_name = line_selection->line_style_name;
        if(line_style_ir.valid()) {
            portrayal_ir.line_styles.push_back(line_style_ir);
        }
    }

    if(const auto area_selection = select_area_portrayal(lookup_index, feature, mariner_settings);
       area_selection.has_value()
       && (!area_selection->fill_color_token.empty() || !area_selection->pattern_name.empty()
           || !area_selection->boundary_line_style_name.empty())) {
        chart_runtime::AreaPatternIR area_pattern_ir;
        area_pattern_ir.instruction = make_instruction_ir(
            chart_runtime::InstructionKind::area_pattern,
            feature.primitive_type,
            "area-pattern",
            area_selection->lookup_key,
            area_selection->lookup_entry);
        area_pattern_ir.fill_color_token = area_selection->fill_color_token;
        area_pattern_ir.pattern_name = area_selection->pattern_name;
        area_pattern_ir.boundary_line_style_name = area_selection->boundary_line_style_name;
        if(area_pattern_ir.valid()) {
            portrayal_ir.area_patterns.push_back(area_pattern_ir);
        }
    }

    if(const auto text_selection = select_text_rules(lookup_index, feature, mariner_settings); text_selection.has_value()) {
        for(std::size_t index = 0; index < text_selection->entries.size(); ++index) {
            const auto& selected_text_rule = text_selection->entries[index];
            chart_runtime::TextRuleIR text_rule_ir;
            text_rule_ir.instruction = make_instruction_ir(
                chart_runtime::InstructionKind::text_rule,
                feature.primitive_type,
                "text-rule",
                text_selection->lookup_key,
                text_selection->lookup_entry,
                index,
                true);
            text_rule_ir.rule_kind = to_runtime_text_rule_kind(selected_text_rule.kind);
            text_rule_ir.instruction_text = selected_text_rule.instruction;
            if(text_rule_ir.valid()) {
                portrayal_ir.text_rules.push_back(text_rule_ir);
            }
        }
    }

    if(const auto priority_selection = select_display_priority(lookup_index, feature, mariner_settings);
       priority_selection.has_value()) {
        chart_runtime::DisplayPriorityIR display_priority_ir;
        display_priority_ir.instruction = make_instruction_ir(
            chart_runtime::InstructionKind::display_priority,
            feature.primitive_type,
            "display-priority",
            priority_selection->lookup_key,
            priority_selection->lookup_entry);
        display_priority_ir.group = to_runtime_display_priority_group(priority_selection->group);
        display_priority_ir.sort_rank = priority_selection->sort_rank;
        display_priority_ir.source_name = priority_selection->source_name;
        if(display_priority_ir.valid()) {
            portrayal_ir.display_priorities.push_back(display_priority_ir);
        }
    }

    return portrayal_ir;
}

}  // namespace marine_chart::s52_core_headless
