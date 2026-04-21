if(NOT DEFINED ZERO_WX_SOURCE_ROOT)
    message(FATAL_ERROR "ZERO_WX_SOURCE_ROOT was not provided")
endif()

set(project_source_files)
foreach(pattern IN ITEMS
    "${ZERO_WX_SOURCE_ROOT}/include/*.h"
    "${ZERO_WX_SOURCE_ROOT}/include/*.hpp"
    "${ZERO_WX_SOURCE_ROOT}/include/*.hh"
    "${ZERO_WX_SOURCE_ROOT}/include/*.c"
    "${ZERO_WX_SOURCE_ROOT}/include/*.cc"
    "${ZERO_WX_SOURCE_ROOT}/include/*.cpp"
    "${ZERO_WX_SOURCE_ROOT}/include/*.cxx"
    "${ZERO_WX_SOURCE_ROOT}/src/*.h"
    "${ZERO_WX_SOURCE_ROOT}/src/*.hpp"
    "${ZERO_WX_SOURCE_ROOT}/src/*.hh"
    "${ZERO_WX_SOURCE_ROOT}/src/*.c"
    "${ZERO_WX_SOURCE_ROOT}/src/*.cc"
    "${ZERO_WX_SOURCE_ROOT}/src/*.cpp"
    "${ZERO_WX_SOURCE_ROOT}/src/*.cxx"
    "${ZERO_WX_SOURCE_ROOT}/apps/*.h"
    "${ZERO_WX_SOURCE_ROOT}/apps/*.hpp"
    "${ZERO_WX_SOURCE_ROOT}/apps/*.hh"
    "${ZERO_WX_SOURCE_ROOT}/apps/*.c"
    "${ZERO_WX_SOURCE_ROOT}/apps/*.cc"
    "${ZERO_WX_SOURCE_ROOT}/apps/*.cpp"
    "${ZERO_WX_SOURCE_ROOT}/apps/*.cxx"
    "${ZERO_WX_SOURCE_ROOT}/test/*.h"
    "${ZERO_WX_SOURCE_ROOT}/test/*.hpp"
    "${ZERO_WX_SOURCE_ROOT}/test/*.hh"
    "${ZERO_WX_SOURCE_ROOT}/test/*.c"
    "${ZERO_WX_SOURCE_ROOT}/test/*.cc"
    "${ZERO_WX_SOURCE_ROOT}/test/*.cpp"
    "${ZERO_WX_SOURCE_ROOT}/test/*.cxx"
)
    file(GLOB_RECURSE matched_files LIST_DIRECTORIES false "${pattern}")
    list(APPEND project_source_files ${matched_files})
endforeach()

list(REMOVE_DUPLICATES project_source_files)

if(project_source_files STREQUAL "")
    message(FATAL_ERROR "No source files found under include/src/apps/test")
endif()

set(forbidden_markers
    "wx/"
    "wxString"
    "wxColour"
    "wxColor"
    "wxPoint"
    "wxPoint2DDouble"
    "wxRect"
    "wxSize"
    "wxBitmap"
    "wxImage"
    "wxFont"
    "wxFileConfig"
    "wxDC"
    "wxGCDC"
    "wxGLContext"
    "wxWindow"
    "glChartCanvas"
)

foreach(project_source_file IN LISTS project_source_files)
    file(READ "${project_source_file}" project_source_text)
    foreach(forbidden_marker IN LISTS forbidden_markers)
        string(FIND "${project_source_text}" "${forbidden_marker}" marker_index)
        if(NOT marker_index EQUAL -1)
            message(FATAL_ERROR
                "Forbidden wx marker '${forbidden_marker}' found in project-owned source: ${project_source_file}")
        endif()
    endforeach()
endforeach()

message(STATUS "Verified zero-wx source markers across include/src/apps/test")
