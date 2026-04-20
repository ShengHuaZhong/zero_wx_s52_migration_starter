if(NOT DEFINED ZERO_WX_RULE_FREEZE_DOC)
    message(FATAL_ERROR "ZERO_WX_RULE_FREEZE_DOC was not provided")
endif()

if(NOT DEFINED ZERO_WX_SOURCE_ROOT)
    message(FATAL_ERROR "ZERO_WX_SOURCE_ROOT was not provided")
endif()

if(NOT EXISTS "${ZERO_WX_RULE_FREEZE_DOC}")
    message(FATAL_ERROR "Zero wx rule freeze doc not found: ${ZERO_WX_RULE_FREEZE_DOC}")
endif()

file(READ "${ZERO_WX_RULE_FREEZE_DOC}" zero_wx_rule_freeze)

foreach(required_marker IN ITEMS
    "wx/*.h"
    "wxString"
    "wxColour"
    "wxBitmap"
    "wxDC"
    "glChartCanvas"
    "find_package(wxWidgets)"
    "Qt6 / QRhi"
    "project-owned IR"
)
    string(FIND "${zero_wx_rule_freeze}" "${required_marker}" marker_index)
    if(marker_index EQUAL -1)
        message(FATAL_ERROR "Zero wx rule freeze doc is missing expected marker: ${required_marker}")
    endif()
endforeach()

set(cmake_files
    "${ZERO_WX_SOURCE_ROOT}/CMakeLists.txt"
)

foreach(cmake_file IN LISTS cmake_files)
    if(EXISTS "${cmake_file}")
        file(READ "${cmake_file}" cmake_text)
        foreach(forbidden_cmake_marker IN ITEMS "find_package(wxWidgets)" "wxWidgets")
            string(FIND "${cmake_text}" "${forbidden_cmake_marker}" marker_index)
            if(NOT marker_index EQUAL -1)
                message(FATAL_ERROR "Project CMake contains forbidden marker '${forbidden_cmake_marker}': ${cmake_file}")
            endif()
        endforeach()
    endif()
endforeach()

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
)
    file(GLOB_RECURSE matched_files LIST_DIRECTORIES false "${pattern}")
    list(APPEND project_source_files ${matched_files})
endforeach()

list(REMOVE_DUPLICATES project_source_files)

foreach(project_source_file IN LISTS project_source_files)
    file(READ "${project_source_file}" project_source_text)
    foreach(forbidden_source_marker IN ITEMS
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
        string(FIND "${project_source_text}" "${forbidden_source_marker}" marker_index)
        if(NOT marker_index EQUAL -1)
            message(FATAL_ERROR "Project-owned source contains forbidden marker '${forbidden_source_marker}': ${project_source_file}")
        endif()
    endforeach()
endforeach()

message(STATUS "Verified zero wx rule freeze doc and current project-owned source/CMake boundaries")
