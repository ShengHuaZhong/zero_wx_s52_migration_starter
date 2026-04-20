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
)
    file(GLOB_RECURSE matched_files LIST_DIRECTORIES false "${pattern}")
    list(APPEND project_source_files ${matched_files})
endforeach()

list(REMOVE_DUPLICATES project_source_files)

foreach(project_source_file IN LISTS project_source_files)
    file(READ "${project_source_file}" project_source_text)
    foreach(forbidden_marker IN ITEMS
        "glChartCanvas"
        "RenderRegionViewOnDC"
        "RenderOverlayRegionViewOnDC"
        "RenderRegionViewOnDCNoText"
        "RenderRegionViewOnDCTextOnly"
        "RenderRegionViewOnGL"
        "RenderOverlayRegionViewOnGL"
        "RenderRegionViewOnGLNoText"
        "RenderViewOnDC"
        "RenderViewOnGLTextOnly"
        "DoRenderRegionViewOnDC"
        "DoRenderRegionViewOnGL"
        "DoRenderOnGL"
        "DoRenderOnGLText"
    )
        string(FIND "${project_source_text}" "${forbidden_marker}" marker_index)
        if(NOT marker_index EQUAL -1)
            message(FATAL_ERROR "Project-owned source contains forbidden old host canvas marker '${forbidden_marker}': ${project_source_file}")
        endif()
    endforeach()
endforeach()

message(STATUS "Verified no project-owned old host canvas paths under include/ and src/")
