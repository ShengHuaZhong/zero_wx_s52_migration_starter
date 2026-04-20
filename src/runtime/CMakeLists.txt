add_library(chart_runtime STATIC)
add_library(marine_chart::chart_runtime ALIAS chart_runtime)

target_sources(chart_runtime
    PRIVATE
        instruction_ir.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
        FILES
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/instruction_ir.h"
)

target_compile_features(chart_runtime PUBLIC cxx_std_20)

target_include_directories(chart_runtime
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
)
