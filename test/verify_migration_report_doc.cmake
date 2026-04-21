if(NOT DEFINED ZERO_WX_MIGRATION_REPORT_DOC)
    message(FATAL_ERROR "ZERO_WX_MIGRATION_REPORT_DOC was not provided")
endif()

if(NOT EXISTS "${ZERO_WX_MIGRATION_REPORT_DOC}")
    message(FATAL_ERROR "Migration report doc not found: ${ZERO_WX_MIGRATION_REPORT_DOC}")
endif()

file(READ "${ZERO_WX_MIGRATION_REPORT_DOC}" migration_report_text)

foreach(required_marker IN ITEMS
    "real-S57 host smoke"
    "golden-image harness"
    "regression-scene-01"
    "regression-scene-02"
    "regression-scene-03"
    "zero-wx-source-verification"
    "zero-wx-build-verification"
    "api-cleanup-freeze"
    "Qt 6 + QRhi"
)
    string(FIND "${migration_report_text}" "${required_marker}" marker_index)
    if(marker_index EQUAL -1)
        message(FATAL_ERROR "Migration report doc is missing expected marker: ${required_marker}")
    endif()
endforeach()

message(STATUS "Verified migration report doc markers")
