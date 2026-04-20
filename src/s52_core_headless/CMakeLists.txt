add_library(s52_core_headless STATIC)
add_library(marine_chart::s52_core_headless ALIAS s52_core_headless)

target_sources(s52_core_headless
    PRIVATE
        module.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
        FILES
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_color.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_string.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/module.h"
)

target_compile_features(s52_core_headless PUBLIC cxx_std_20)

target_include_directories(s52_core_headless
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
)
