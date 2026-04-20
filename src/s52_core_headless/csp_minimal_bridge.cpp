#include "marine_chart/s52_core_headless/csp_minimal_bridge.h"

namespace marine_chart::s52_core_headless {
namespace {

[[nodiscard]] CspProcedureId resolve_csp_procedure_id(NeutralStringView entry_name) noexcept {
    if(entry_name == "CLRLIN01") {
        return CspProcedureId::clrlin01;
    }

    if(entry_name == "DATCVR01") {
        return CspProcedureId::datcvr01;
    }

    if(entry_name == "DEPARE01") {
        return CspProcedureId::depare01;
    }

    if(entry_name == "DEPARE02") {
        return CspProcedureId::depare02;
    }

    if(entry_name == "DEPCNT02") {
        return CspProcedureId::depcnt02;
    }

    if(entry_name == "LEGLIN02") {
        return CspProcedureId::leglin02;
    }

    if(entry_name == "LIGHTS05") {
        return CspProcedureId::lights05;
    }

    if(entry_name == "OBSTRN04") {
        return CspProcedureId::obstrn04;
    }

    if(entry_name == "OWNSHP02") {
        return CspProcedureId::ownshp02;
    }

    if(entry_name == "PASTRK01") {
        return CspProcedureId::pastrk01;
    }

    if(entry_name == "QUAPOS01") {
        return CspProcedureId::quapos01;
    }

    if(entry_name == "RESARE01") {
        return CspProcedureId::resare01;
    }

    if(entry_name == "RESARE02") {
        return CspProcedureId::resare02;
    }

    if(entry_name == "RESTRN01") {
        return CspProcedureId::restrn01;
    }

    if(entry_name == "SLCONS03") {
        return CspProcedureId::slcons03;
    }

    if(entry_name == "SOUNDG02") {
        return CspProcedureId::soundg02;
    }

    if(entry_name == "SYMINS01") {
        return CspProcedureId::symins01;
    }

    if(entry_name == "TOPMAR01") {
        return CspProcedureId::topmar01;
    }

    if(entry_name == "TOPMARI1") {
        return CspProcedureId::topmari1;
    }

    if(entry_name == "VESSEL01") {
        return CspProcedureId::vessel01;
    }

    if(entry_name == "VRMEBL01") {
        return CspProcedureId::vrmebl01;
    }

    if(entry_name == "WRECKS02") {
        return CspProcedureId::wrecks02;
    }

    return CspProcedureId::unsupported;
}

}  // namespace

CspDispatchRequest bridge_csp_entry_name(
    NeutralStringView entry_name,
    const MarinerSettings&) noexcept {
    if(entry_name.empty()) {
        return {};
    }

    return {
        resolve_csp_procedure_id(entry_name),
        make_neutral_string(entry_name)
    };
}

CspDispatchRequest bridge_csp_instruction(
    NeutralStringView instruction,
    const MarinerSettings& mariner_settings) noexcept {
    const auto csp_begin = instruction.find("CS(");
    if(csp_begin == NeutralStringView::npos) {
        return {};
    }

    const auto name_begin = csp_begin + 3;
    const auto name_end = instruction.find_first_of(");", name_begin);
    if(name_end == NeutralStringView::npos) {
        return {};
    }

    return bridge_csp_entry_name(instruction.substr(name_begin, name_end - name_begin), mariner_settings);
}

}  // namespace marine_chart::s52_core_headless
