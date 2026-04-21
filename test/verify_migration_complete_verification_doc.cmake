if(NOT DEFINED ZERO_WX_MIGRATION_COMPLETE_VERIFICATION_DOC)
    message(FATAL_ERROR "ZERO_WX_MIGRATION_COMPLETE_VERIFICATION_DOC was not provided")
endif()

if(NOT EXISTS "${ZERO_WX_MIGRATION_COMPLETE_VERIFICATION_DOC}")
    message(FATAL_ERROR "Migration complete verification doc not found: ${ZERO_WX_MIGRATION_COMPLETE_VERIFICATION_DOC}")
endif()

file(READ "${ZERO_WX_MIGRATION_COMPLETE_VERIFICATION_DOC}" verification_doc_text)

foreach(required_marker IN ITEMS
    "Final Acceptance Checklist"
    "Qt 6 + QRhi"
    "zero-wx"
    "Real-S57"
    "scene-01/02/03"
    "ctest --preset test-windows-msvc-debug --output-on-failure"
)
    string(FIND "${verification_doc_text}" "${required_marker}" marker_index)
    if(marker_index EQUAL -1)
        message(FATAL_ERROR "Migration complete verification doc is missing expected marker: ${required_marker}")
    endif()
endforeach()

message(STATUS "Verified migration complete verification doc markers")
