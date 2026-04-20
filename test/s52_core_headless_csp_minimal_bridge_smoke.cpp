#include "marine_chart/s52_core_headless/csp_minimal_bridge.h"

int main() {
    const auto mariner_settings = marine_chart::s52_core_headless::make_default_mariner_settings();

    const auto restrn = marine_chart::s52_core_headless::bridge_csp_entry_name(
        "RESTRN01",
        mariner_settings);
    if(!restrn.requested() || !restrn.recognized()
        || restrn.procedure != marine_chart::s52_core_headless::CspProcedureId::restrn01) {
        return 1;
    }

    const auto topmari1 = marine_chart::s52_core_headless::bridge_csp_entry_name(
        "TOPMARI1",
        mariner_settings);
    if(!topmari1.recognized()
        || topmari1.procedure != marine_chart::s52_core_headless::CspProcedureId::topmari1) {
        return 2;
    }

    const auto unsupported = marine_chart::s52_core_headless::bridge_csp_entry_name(
        "NOTREAL01",
        mariner_settings);
    if(!unsupported.requested() || unsupported.recognized()
        || unsupported.procedure != marine_chart::s52_core_headless::CspProcedureId::unsupported) {
        return 3;
    }

    const auto from_instruction = marine_chart::s52_core_headless::bridge_csp_instruction(
        "SY(ACHARE02);LS(DASH,2,CHMGF);CS(RESTRN01)",
        mariner_settings);
    if(!from_instruction.recognized() || from_instruction.entry_name != "RESTRN01") {
        return 4;
    }

    const auto malformed_vendor_instruction = marine_chart::s52_core_headless::bridge_csp_instruction(
        "SY(LNDARE01);CS(QUAPOS01;TX(OBJNAM,1,2,3,'15118',-1,-1,CHBLK,26))",
        mariner_settings);
    if(!malformed_vendor_instruction.recognized()
        || malformed_vendor_instruction.procedure != marine_chart::s52_core_headless::CspProcedureId::quapos01) {
        return 5;
    }

    const auto no_request = marine_chart::s52_core_headless::bridge_csp_instruction(
        "SY(ACHARE51);LS(DASH,2,CHMGF)",
        mariner_settings);
    if(no_request.requested() || no_request.procedure != marine_chart::s52_core_headless::CspProcedureId::none) {
        return 6;
    }

    return 0;
}
