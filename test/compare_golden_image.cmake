if(NOT DEFINED ZERO_WX_GOLDEN_EXPECTED)
    message(FATAL_ERROR "ZERO_WX_GOLDEN_EXPECTED was not provided")
endif()

if(NOT DEFINED ZERO_WX_GOLDEN_ACTUAL)
    message(FATAL_ERROR "ZERO_WX_GOLDEN_ACTUAL was not provided")
endif()

if(NOT EXISTS "${ZERO_WX_GOLDEN_EXPECTED}")
    message(FATAL_ERROR "Golden expected image not found: ${ZERO_WX_GOLDEN_EXPECTED}")
endif()

if(NOT EXISTS "${ZERO_WX_GOLDEN_ACTUAL}")
    message(FATAL_ERROR "Golden actual image not found: ${ZERO_WX_GOLDEN_ACTUAL}")
endif()

file(SHA256 "${ZERO_WX_GOLDEN_EXPECTED}" expected_sha256)
file(SHA256 "${ZERO_WX_GOLDEN_ACTUAL}" actual_sha256)

if(NOT expected_sha256 STREQUAL actual_sha256)
    set(golden_name "unnamed")
    if(DEFINED ZERO_WX_GOLDEN_NAME AND NOT ZERO_WX_GOLDEN_NAME STREQUAL "")
        set(golden_name "${ZERO_WX_GOLDEN_NAME}")
    endif()

    message(FATAL_ERROR
        "Golden image mismatch for ${golden_name}: "
        "expected=${expected_sha256}, actual=${actual_sha256}")
endif()

message(STATUS "Golden image compare matched: ${ZERO_WX_GOLDEN_ACTUAL}")
