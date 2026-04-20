if(NOT DEFINED ZERO_WX_HEADLESS_BOUNDARY_DOC)
    message(FATAL_ERROR "ZERO_WX_HEADLESS_BOUNDARY_DOC was not provided")
endif()

if(NOT EXISTS "${ZERO_WX_HEADLESS_BOUNDARY_DOC}")
    message(FATAL_ERROR "Headless boundary design doc not found: ${ZERO_WX_HEADLESS_BOUNDARY_DOC}")
endif()

file(READ "${ZERO_WX_HEADLESS_BOUNDARY_DOC}" headless_boundary_design)

foreach(required_marker IN ITEMS
    "s52_core_headless"
    "chart_runtime"
    "chart_qt_host"
    "InstructionIR"
    "Qt6 / QRhi"
    "chartsymbols.xml"
    "ogrs57datasource.cpp"
    "DepthFont.*"
    "TexFont.*"
    "wxDC"
    "wxGLContext"
    "glChartCanvas"
)
    string(FIND "${headless_boundary_design}" "${required_marker}" marker_index)
    if(marker_index EQUAL -1)
        message(FATAL_ERROR "Headless boundary design doc is missing expected marker: ${required_marker}")
    endif()
endforeach()

message(STATUS "Verified headless boundary design doc: ${ZERO_WX_HEADLESS_BOUNDARY_DOC}")
