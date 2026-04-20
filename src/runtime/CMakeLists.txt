add_library(chart_runtime STATIC)
add_library(marine_chart::chart_runtime ALIAS chart_runtime)

target_sources(chart_runtime
    PRIVATE
        area_renderer.cpp
        area_pattern_ir.cpp
        display_priority_ir.cpp
        feature_portrayal_ir.cpp
        instruction_ir.cpp
        priority_sorter.cpp
        line_style_ir.cpp
        line_style_parser.cpp
        line_renderer.cpp
        pattern_atlas_loader.cpp
        point_symbol_ir.cpp
        point_symbol_atlas_loader.cpp
        point_renderer.cpp
        portrayal_ir_debug_dump.cpp
        portrayal_ir_ingestion.cpp
        runtime_palette_colors.cpp
        text_layout.cpp
        text_rule_ir.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
        FILES
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/area_renderer.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/area_pattern_ir.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/display_priority_ir.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/feature_portrayal_ir.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/instruction_ir.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/line_style_ir.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/line_style_parser.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/line_renderer.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/pattern_atlas_loader.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/point_symbol_ir.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/point_symbol_atlas_loader.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/point_renderer.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/portrayal_ir_debug_dump.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/portrayal_ir_ingestion.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/priority_sorter.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/runtime_palette_colors.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/text_layout.h"
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_runtime/text_rule_ir.h"
)

target_compile_features(chart_runtime PUBLIC cxx_std_20)

target_include_directories(chart_runtime
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
)
