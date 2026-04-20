#include "marine_chart/chart_runtime/portrayal_ir_debug_dump.h"

#include <ostream>
#include <sstream>

namespace marine_chart::chart_runtime {
namespace {

void dump_instruction_header(std::ostream& stream, const InstructionIR& instruction) {
    stream << " id=" << instruction.stable_id;
    stream << " object_class=" << instruction.source.object_class;
    stream << " lookup_id=" << instruction.source.lookup_id;
}

}  // namespace

std::string dump_feature_portrayal_ir(const FeaturePortrayalIR& portrayal_ir) {
    std::ostringstream stream;
    stream << "feature_portrayal_ir\n";
    stream << "point_symbols: " << portrayal_ir.point_symbols.size() << "\n";
    for(const auto& point_symbol : portrayal_ir.point_symbols) {
        stream << "point_symbol";
        dump_instruction_header(stream, point_symbol.instruction);
        stream << " symbol=" << point_symbol.symbol_name << "\n";
    }

    stream << "line_styles: " << portrayal_ir.line_styles.size() << "\n";
    for(const auto& line_style : portrayal_ir.line_styles) {
        stream << "line_style";
        dump_instruction_header(stream, line_style.instruction);
        stream << " style=" << line_style.line_style_name << "\n";
    }

    stream << "area_patterns: " << portrayal_ir.area_patterns.size() << "\n";
    for(const auto& area_pattern : portrayal_ir.area_patterns) {
        stream << "area_pattern";
        dump_instruction_header(stream, area_pattern.instruction);
        stream << " fill=" << area_pattern.fill_color_token;
        stream << " pattern=" << area_pattern.pattern_name;
        stream << " boundary=" << area_pattern.boundary_line_style_name << "\n";
    }

    stream << "text_rules: " << portrayal_ir.text_rules.size() << "\n";
    for(const auto& text_rule : portrayal_ir.text_rules) {
        stream << "text_rule";
        dump_instruction_header(stream, text_rule.instruction);
        stream << " text=" << text_rule.instruction_text << "\n";
    }

    stream << "display_priorities: " << portrayal_ir.display_priorities.size() << "\n";
    for(const auto& display_priority : portrayal_ir.display_priorities) {
        stream << "display_priority";
        dump_instruction_header(stream, display_priority.instruction);
        stream << " source=" << display_priority.source_name;
        stream << " sort_rank=" << display_priority.sort_rank << "\n";
    }

    return stream.str();
}

}  // namespace marine_chart::chart_runtime
