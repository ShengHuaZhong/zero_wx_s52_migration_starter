if(NOT DEFINED ZERO_WX_REGRESSION_SCENE_POLICY_DOC)
    message(FATAL_ERROR "ZERO_WX_REGRESSION_SCENE_POLICY_DOC was not provided")
endif()

if(NOT EXISTS "${ZERO_WX_REGRESSION_SCENE_POLICY_DOC}")
    message(FATAL_ERROR "Regression scene policy doc not found: ${ZERO_WX_REGRESSION_SCENE_POLICY_DOC}")
endif()

file(READ "${ZERO_WX_REGRESSION_SCENE_POLICY_DOC}" regression_scene_policy)

foreach(required_marker IN ITEMS
    "S57_TESTDATA_ROOT"
    "scene-01"
    "scene-02"
    "scene-03"
    "chart_standalone"
    "chart_runtime"
    "golden"
    "skip"
    "no wx"
)
    string(FIND "${regression_scene_policy}" "${required_marker}" marker_index)
    if(marker_index EQUAL -1)
        message(FATAL_ERROR "Regression scene policy doc is missing expected marker: ${required_marker}")
    endif()
endforeach()

message(STATUS "Verified regression scene policy doc: ${ZERO_WX_REGRESSION_SCENE_POLICY_DOC}")
