if(NOT DEFINED ZERO_WX_SOURCE_ROOT)
    message(FATAL_ERROR "ZERO_WX_SOURCE_ROOT was not provided")
endif()

if(NOT DEFINED ZERO_WX_BUILD_ROOT)
    message(FATAL_ERROR "ZERO_WX_BUILD_ROOT was not provided")
endif()

if(POLICY CMP0207)
    cmake_policy(SET CMP0207 NEW)
endif()

set(project_cmake_files
    "${ZERO_WX_SOURCE_ROOT}/CMakeLists.txt"
    "${ZERO_WX_SOURCE_ROOT}/src/runtime/CMakeLists.txt"
    "${ZERO_WX_SOURCE_ROOT}/src/s52_core_headless/CMakeLists.txt"
    "${ZERO_WX_SOURCE_ROOT}/src/qt_host/CMakeLists.txt"
    "${ZERO_WX_SOURCE_ROOT}/apps/chart_standalone/CMakeLists.txt"
)

foreach(project_cmake_file IN LISTS project_cmake_files)
    if(EXISTS "${project_cmake_file}")
        file(READ "${project_cmake_file}" project_cmake_text)
        foreach(forbidden_marker IN ITEMS "find_package(wxWidgets)" "wxWidgets")
            string(FIND "${project_cmake_text}" "${forbidden_marker}" marker_index)
            if(NOT marker_index EQUAL -1)
                message(FATAL_ERROR
                    "Forbidden build marker '${forbidden_marker}' found in project CMake: ${project_cmake_file}")
            endif()
        endforeach()
    endif()
endforeach()

set(build_text_files
    "${ZERO_WX_BUILD_ROOT}/CMakeCache.txt"
)
file(GLOB_RECURSE generated_cmake_files LIST_DIRECTORIES false
    "${ZERO_WX_BUILD_ROOT}/CMakeFiles/*.cmake")
list(APPEND build_text_files ${generated_cmake_files})
list(REMOVE_DUPLICATES build_text_files)

foreach(build_text_file IN LISTS build_text_files)
    if(EXISTS "${build_text_file}")
        file(READ "${build_text_file}" build_text)
        string(TOLOWER "${build_text}" build_text_lower)
        foreach(forbidden_marker IN ITEMS "wxwidgets" "wxmsw" "wxbase")
            string(FIND "${build_text_lower}" "${forbidden_marker}" marker_index)
            if(NOT marker_index EQUAL -1)
                message(FATAL_ERROR
                    "Forbidden wx build marker '${forbidden_marker}' found in generated build text: ${build_text_file}")
            endif()
        endforeach()
    endif()
endforeach()

if(DEFINED ZERO_WX_EXECUTABLES AND NOT ZERO_WX_EXECUTABLES STREQUAL "")
    set(runtime_dependency_targets)
    foreach(candidate_executable IN LISTS ZERO_WX_EXECUTABLES)
        if(EXISTS "${candidate_executable}")
            list(APPEND runtime_dependency_targets "${candidate_executable}")
        endif()
    endforeach()

    if(NOT runtime_dependency_targets STREQUAL "")
        foreach(runtime_dependency_target IN LISTS runtime_dependency_targets)
            file(GET_RUNTIME_DEPENDENCIES
                RESOLVED_DEPENDENCIES_VAR resolved_dependencies
                UNRESOLVED_DEPENDENCIES_VAR unresolved_dependencies
                EXECUTABLES "${runtime_dependency_target}"
            )

            foreach(resolved_dependency IN LISTS resolved_dependencies)
                get_filename_component(resolved_dependency_name "${resolved_dependency}" NAME)
                string(TOLOWER "${resolved_dependency_name}" resolved_dependency_name_lower)
                if(resolved_dependency_name_lower MATCHES "^wx")
                    message(FATAL_ERROR
                        "Forbidden wx runtime dependency found: ${resolved_dependency}")
                endif()
            endforeach()
        endforeach()
    endif()
endif()

message(STATUS "Verified zero-wx build configuration and runtime dependency boundaries")
