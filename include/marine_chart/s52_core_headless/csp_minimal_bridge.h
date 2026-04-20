#pragma once

#include "marine_chart/s52_core_headless/mariner_settings.h"
#include "marine_chart/s52_core_headless/neutral_string.h"

#include <cstdint>

namespace marine_chart::s52_core_headless {

enum class CspProcedureId : std::uint8_t {
    none,
    unsupported,
    clrlin01,
    datcvr01,
    depare01,
    depare02,
    depcnt02,
    leglin02,
    lights05,
    obstrn04,
    ownshp02,
    pastrk01,
    quapos01,
    resare01,
    resare02,
    restrn01,
    slcons03,
    soundg02,
    symins01,
    topmar01,
    topmari1,
    vessel01,
    vrmebl01,
    wrecks02
};

struct CspDispatchRequest final {
    CspProcedureId procedure{CspProcedureId::none};
    NeutralString entry_name;

    [[nodiscard]] bool requested() const noexcept {
        return !entry_name.empty();
    }

    [[nodiscard]] bool recognized() const noexcept {
        return procedure != CspProcedureId::none && procedure != CspProcedureId::unsupported;
    }

    bool operator==(const CspDispatchRequest&) const noexcept = default;
};

[[nodiscard]] CspDispatchRequest bridge_csp_entry_name(
    NeutralStringView entry_name,
    const MarinerSettings& mariner_settings) noexcept;

[[nodiscard]] CspDispatchRequest bridge_csp_instruction(
    NeutralStringView instruction,
    const MarinerSettings& mariner_settings) noexcept;

}  // namespace marine_chart::s52_core_headless
