add_library(s52_core_headless STATIC)
add_library(marine_chart::s52_core_headless ALIAS s52_core_headless)

target_sources(s52_core_headless
    PRIVATE
        chartsymbols_xml_loader.cpp
        neutral_config_loader.cpp
        module.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
        FILES
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/asset_catalog_types.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/chartsymbols_xml_loader.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_color.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_config_loader.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_containers.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_font_descriptor.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_geometry.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_image_metadata.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_string.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/module.h"
)

target_compile_features(s52_core_headless PUBLIC cxx_std_20)

target_include_directories(s52_core_headless
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
)
