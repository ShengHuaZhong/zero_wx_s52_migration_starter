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
endif()
