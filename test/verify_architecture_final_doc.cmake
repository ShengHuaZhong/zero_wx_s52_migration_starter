if(NOT DEFINED ZERO_WX_ARCHITECTURE_FINAL_DOC)
    message(FATAL_ERROR "ZERO_WX_ARCHITECTURE_FINAL_DOC was not provided")
endif()

if(NOT EXISTS "${ZERO_WX_ARCHITECTURE_FINAL_DOC}")
    message(FATAL_ERROR "Architecture final doc not found: ${ZERO_WX_ARCHITECTURE_FINAL_DOC}")
endif()

file(READ "${ZERO_WX_ARCHITECTURE_FINAL_DOC}" architecture_final_text)

foreach(required_marker IN ITEMS
    "s52_core_headless"
    "chart_runtime"
    "chart_qt_host"
    "Qt 6 + QRhi"
    "S57_TESTDATA_ROOT"
    "regression-scene-01"
    "zero-wx-source-verification"
    "zero-wx-build-verification"
    "api-cleanup-freeze"
)
    string(FIND "${architecture_final_text}" "${required_marker}" marker_index)
    if(marker_index EQUAL -1)
        message(FATAL_ERROR "Architecture final doc is missing expected marker: ${required_marker}")
    endif()
endforeach()

message(STATUS "Verified architecture final doc markers")
