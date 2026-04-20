add_library(s52_core_headless STATIC)
add_library(marine_chart::s52_core_headless ALIAS s52_core_headless)

target_sources(s52_core_headless
    PRIVATE
        area_portrayal_selection.cpp
        csp_entry_audit.cpp
        csp_minimal_bridge.cpp
        chartsymbols_xml_loader.cpp
        color_table_loader.cpp
        csv_dictionary_loader.cpp
        feature_attribute_adapter.cpp
        headless_core_init.cpp
        line_portrayal_selection.cpp
        line_style_loader.cpp
        lookup_index.cpp
        lookup_key.cpp
        lookup_raw_loader.cpp
        neutral_config_loader.cpp
        module.cpp
        pattern_catalog_loader.cpp
        point_portrayal_selection.cpp
        symbol_catalog_loader.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
        FILES
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/area_portrayal_selection.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/asset_catalog_types.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/chartsymbols_xml_loader.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/color_table_loader.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/csp_entry_audit.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/csp_minimal_bridge.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/csv_dictionary_loader.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/feature_attribute_adapter.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/headless_core_init.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/line_portrayal_selection.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/line_style_loader.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/lookup_index.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/lookup_key.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/lookup_raw_loader.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/mariner_settings.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_color.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_config_loader.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_containers.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_font_descriptor.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_geometry.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_image_metadata.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/neutral_string.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/point_portrayal_selection.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/module.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/pattern_catalog_loader.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/s52_core_headless/symbol_catalog_loader.h"
)

target_compile_features(s52_core_headless PUBLIC cxx_std_20)

target_include_directories(s52_core_headless
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
)
