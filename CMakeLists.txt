cmake_minimum_required(VERSION 3.29)

project(zero_wx_s52_migration_starter VERSION 0.1.0 LANGUAGES CXX)

include(CTest)

set(ZERO_WX_EMPTY_SMOKE_STAMP "${CMAKE_BINARY_DIR}/empty-smoke.stamp")

add_subdirectory(src/s52_core_headless)

add_custom_target(empty_smoke ALL
    COMMAND "${CMAKE_COMMAND}" -E echo "Running empty smoke build"
    COMMAND "${CMAKE_COMMAND}" -E touch "${ZERO_WX_EMPTY_SMOKE_STAMP}"
    BYPRODUCTS "${ZERO_WX_EMPTY_SMOKE_STAMP}"
    COMMENT "Producing the empty smoke build marker"
    VERBATIM
)

if(BUILD_TESTING)
    add_executable(s52_core_headless_module_smoke
        test/s52_core_headless_module_smoke.cpp
    )

    target_link_libraries(s52_core_headless_module_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    add_test(
        NAME empty-smoke
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_EMPTY_SMOKE_STAMP:FILEPATH=${ZERO_WX_EMPTY_SMOKE_STAMP}"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_empty_smoke.cmake"
    )

    add_test(
        NAME s52-core-headless-module-smoke
        COMMAND s52_core_headless_module_smoke
    )

    add_test(
        NAME s57data-asset-presence
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_S57DATA_ROOT:PATH=${CMAKE_CURRENT_SOURCE_DIR}/vendor/opencpn_s57data"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_s57data_assets.cmake"
    )

    add_test(
        NAME headless-boundary-design-doc
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_HEADLESS_BOUNDARY_DOC:FILEPATH=${CMAKE_CURRENT_SOURCE_DIR}/docs/headless_boundary_design.md"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_headless_boundary_design.cmake"
    )

    add_test(
        NAME zero-wx-rule-freeze
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_RULE_FREEZE_DOC:FILEPATH=${CMAKE_CURRENT_SOURCE_DIR}/docs/zero_wx_rule_freeze.md"
            "-DZERO_WX_SOURCE_ROOT:PATH=${CMAKE_CURRENT_SOURCE_DIR}"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_zero_wx_rule_freeze.cmake"
    )

    add_test(
        NAME remove-wxdc-paths
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_SOURCE_ROOT:PATH=${CMAKE_CURRENT_SOURCE_DIR}"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_no_wxdc_paths.cmake"
    )

    add_test(
        NAME remove-wxgcdc-paths
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_SOURCE_ROOT:PATH=${CMAKE_CURRENT_SOURCE_DIR}"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_no_wxgcdc_paths.cmake"
    )
endif()
