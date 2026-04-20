cmake_minimum_required(VERSION 3.29)

project(zero_wx_s52_migration_starter VERSION 0.1.0 LANGUAGES NONE)

include(CTest)

set(ZERO_WX_EMPTY_SMOKE_STAMP "${CMAKE_BINARY_DIR}/empty-smoke.stamp")

add_custom_target(empty_smoke ALL
    COMMAND "${CMAKE_COMMAND}" -E echo "Running empty smoke build"
    COMMAND "${CMAKE_COMMAND}" -E touch "${ZERO_WX_EMPTY_SMOKE_STAMP}"
    BYPRODUCTS "${ZERO_WX_EMPTY_SMOKE_STAMP}"
    COMMENT "Producing the empty smoke build marker"
    VERBATIM
)

if(BUILD_TESTING)
    add_test(
        NAME empty-smoke
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_EMPTY_SMOKE_STAMP:FILEPATH=${ZERO_WX_EMPTY_SMOKE_STAMP}"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_empty_smoke.cmake"
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
endif()
