cmake_minimum_required(VERSION 3.29)

project(zero_wx_s52_migration_starter VERSION 0.1.0 LANGUAGES CXX)

include(CTest)

set(ZERO_WX_EMPTY_SMOKE_STAMP "${CMAKE_BINARY_DIR}/empty-smoke.stamp")

add_subdirectory(src/runtime)
add_subdirectory(src/s52_core_headless)

set(ZERO_WX_ENABLE_QT_HOST ON CACHE BOOL "Build the Qt host module when Qt6 Widgets is available")
if(ZERO_WX_ENABLE_QT_HOST)
    find_package(
        Qt6 6.8
        COMPONENTS Widgets
        QUIET
        PATHS "$ENV{QT_ROOT}"
        PATH_SUFFIXES lib/cmake/Qt6
    )

    if(Qt6_FOUND)
        add_subdirectory(src/qt_host)
        add_subdirectory(apps)
    else()
        message(STATUS "Qt6 Widgets not found; skipping chart_qt_host")
    endif()
endif()

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

    add_executable(s52_core_headless_init_smoke
        test/s52_core_headless_init_smoke.cpp
    )

    add_executable(s52_core_headless_lookup_raw_smoke
        test/s52_core_headless_lookup_raw_smoke.cpp
    )

    add_executable(s52_core_headless_lookup_index_smoke
        test/s52_core_headless_lookup_index_smoke.cpp
    )

    add_executable(s52_core_headless_mariner_settings_smoke
        test/s52_core_headless_mariner_settings_smoke.cpp
    )

    add_executable(s52_core_headless_csp_entry_audit_smoke
        test/s52_core_headless_csp_entry_audit_smoke.cpp
    )

    add_executable(s52_core_headless_csp_minimal_bridge_smoke
        test/s52_core_headless_csp_minimal_bridge_smoke.cpp
    )

    add_executable(s52_core_headless_feature_attribute_adapter_smoke
        test/s52_core_headless_feature_attribute_adapter_smoke.cpp
    )

    add_executable(s52_core_headless_lookup_key_smoke
        test/s52_core_headless_lookup_key_smoke.cpp
    )

    add_executable(s52_core_headless_point_portrayal_selection_smoke
        test/s52_core_headless_point_portrayal_selection_smoke.cpp
    )

    add_executable(s52_core_headless_line_portrayal_selection_smoke
        test/s52_core_headless_line_portrayal_selection_smoke.cpp
    )

    add_executable(s52_core_headless_area_portrayal_selection_smoke
        test/s52_core_headless_area_portrayal_selection_smoke.cpp
    )

    add_executable(s52_core_headless_text_rule_selection_smoke
        test/s52_core_headless_text_rule_selection_smoke.cpp
    )

    add_executable(s52_core_headless_display_priority_selection_smoke
        test/s52_core_headless_display_priority_selection_smoke.cpp
    )

    add_executable(s52_core_headless_portrayal_ir_pipeline_smoke
        test/s52_core_headless_portrayal_ir_pipeline_smoke.cpp
    )

    add_executable(s52_core_headless_rule_engine_smoke
        test/s52_core_headless_rule_engine_smoke.cpp
    )

    add_executable(chart_runtime_instruction_ir_smoke
        test/chart_runtime_instruction_ir_smoke.cpp
    )

    add_executable(chart_runtime_point_symbol_ir_smoke
        test/chart_runtime_point_symbol_ir_smoke.cpp
    )

    add_executable(chart_runtime_line_style_ir_smoke
        test/chart_runtime_line_style_ir_smoke.cpp
    )

    add_executable(chart_runtime_area_pattern_ir_smoke
        test/chart_runtime_area_pattern_ir_smoke.cpp
    )

    add_executable(chart_runtime_area_renderer_smoke
        test/chart_runtime_area_renderer_smoke.cpp
    )

    add_executable(chart_runtime_text_rule_ir_smoke
        test/chart_runtime_text_rule_ir_smoke.cpp
    )

    add_executable(chart_runtime_text_layout_smoke
        test/chart_runtime_text_layout_smoke.cpp
    )

    add_executable(chart_runtime_text_renderer_smoke
        test/chart_runtime_text_renderer_smoke.cpp
    )

    add_executable(chart_runtime_display_priority_ir_smoke
        test/chart_runtime_display_priority_ir_smoke.cpp
    )

    add_executable(chart_runtime_portrayal_ir_debug_dump_smoke
        test/chart_runtime_portrayal_ir_debug_dump_smoke.cpp
    )

    add_executable(chart_runtime_portrayal_ir_ingestion_smoke
        test/chart_runtime_portrayal_ir_ingestion_smoke.cpp
    )

    add_executable(chart_runtime_priority_sorter_smoke
        test/chart_runtime_priority_sorter_smoke.cpp
    )

    add_executable(chart_runtime_runtime_palette_colors_smoke
        test/chart_runtime_runtime_palette_colors_smoke.cpp
    )

    add_executable(chart_runtime_runtime_render_frame_smoke
        test/chart_runtime_runtime_render_frame_smoke.cpp
    )

    add_executable(chart_runtime_point_symbol_atlas_loader_smoke
        test/chart_runtime_point_symbol_atlas_loader_smoke.cpp
    )

    add_executable(chart_runtime_point_renderer_smoke
        test/chart_runtime_point_renderer_smoke.cpp
    )

    add_executable(chart_runtime_line_style_parser_smoke
        test/chart_runtime_line_style_parser_smoke.cpp
    )

    add_executable(chart_runtime_line_renderer_smoke
        test/chart_runtime_line_renderer_smoke.cpp
    )

    add_executable(chart_runtime_open_chart_flow_smoke
        test/chart_runtime_open_chart_flow_smoke.cpp
    )

    add_executable(chart_runtime_s57_dataset_ingestion_smoke
        test/chart_runtime_s57_dataset_ingestion_smoke.cpp
    )

    add_executable(chart_runtime_pattern_atlas_loader_smoke
        test/chart_runtime_pattern_atlas_loader_smoke.cpp
    )

    target_link_libraries(s52_core_headless_module_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_init_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_lookup_raw_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_lookup_index_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_mariner_settings_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_csp_entry_audit_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_csp_minimal_bridge_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_feature_attribute_adapter_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_lookup_key_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_point_portrayal_selection_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_line_portrayal_selection_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_area_portrayal_selection_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_text_rule_selection_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_display_priority_selection_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_portrayal_ir_pipeline_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(s52_core_headless_rule_engine_smoke
        PRIVATE
            marine_chart::s52_core_headless
    )

    target_link_libraries(chart_runtime_instruction_ir_smoke
        PRIVATE
            marine_chart::chart_runtime
    )

    target_link_libraries(chart_runtime_point_symbol_ir_smoke
        PRIVATE
            marine_chart::chart_runtime
    )

    target_link_libraries(chart_runtime_line_style_ir_smoke
        PRIVATE
            marine_chart::chart_runtime
    )

    target_link_libraries(chart_runtime_area_pattern_ir_smoke
        PRIVATE
            marine_chart::chart_runtime
    )

    target_link_libraries(chart_runtime_area_renderer_smoke
        PRIVATE
            marine_chart::chart_runtime
            marine_chart::s52_core_headless
    )

    target_link_libraries(chart_runtime_text_rule_ir_smoke
        PRIVATE
            marine_chart::chart_runtime
    )

    target_link_libraries(chart_runtime_text_layout_smoke
        PRIVATE
            marine_chart::chart_runtime
    )

    target_link_libraries(chart_runtime_text_renderer_smoke
        PRIVATE
            marine_chart::chart_runtime
    )

    target_link_libraries(chart_runtime_display_priority_ir_smoke
        PRIVATE
            marine_chart::chart_runtime
    )

    target_link_libraries(chart_runtime_portrayal_ir_debug_dump_smoke
        PRIVATE
            marine_chart::chart_runtime
    )

    target_link_libraries(chart_runtime_portrayal_ir_ingestion_smoke
        PRIVATE
            marine_chart::chart_runtime
    )

    target_link_libraries(chart_runtime_priority_sorter_smoke
        PRIVATE
            marine_chart::chart_runtime
    )

    target_link_libraries(chart_runtime_runtime_palette_colors_smoke
        PRIVATE
            marine_chart::chart_runtime
    )

    target_link_libraries(chart_runtime_runtime_render_frame_smoke
        PRIVATE
            marine_chart::chart_runtime
            marine_chart::s52_core_headless
    )

    target_link_libraries(chart_runtime_point_symbol_atlas_loader_smoke
        PRIVATE
            marine_chart::chart_runtime
            marine_chart::s52_core_headless
    )

    target_link_libraries(chart_runtime_point_renderer_smoke
        PRIVATE
            marine_chart::chart_runtime
            marine_chart::s52_core_headless
    )

    target_link_libraries(chart_runtime_line_style_parser_smoke
        PRIVATE
            marine_chart::chart_runtime
    )

    target_link_libraries(chart_runtime_line_renderer_smoke
        PRIVATE
            marine_chart::chart_runtime
    )

    target_link_libraries(chart_runtime_open_chart_flow_smoke
        PRIVATE
            marine_chart::chart_runtime
            marine_chart::s52_core_headless
    )

    target_link_libraries(chart_runtime_s57_dataset_ingestion_smoke
        PRIVATE
            marine_chart::chart_runtime
            marine_chart::s52_core_headless
    )

    target_link_libraries(chart_runtime_pattern_atlas_loader_smoke
        PRIVATE
            marine_chart::chart_runtime
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
    set_tests_properties(s52-core-headless-module-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-init-smoke
        COMMAND s52_core_headless_init_smoke
    )
    set_tests_properties(s52-core-headless-init-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-lookup-raw-smoke
        COMMAND s52_core_headless_lookup_raw_smoke
    )
    set_tests_properties(s52-core-headless-lookup-raw-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-lookup-index-smoke
        COMMAND s52_core_headless_lookup_index_smoke
    )
    set_tests_properties(s52-core-headless-lookup-index-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-mariner-settings-smoke
        COMMAND s52_core_headless_mariner_settings_smoke
    )
    set_tests_properties(s52-core-headless-mariner-settings-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-csp-entry-audit-smoke
        COMMAND s52_core_headless_csp_entry_audit_smoke
    )
    set_tests_properties(s52-core-headless-csp-entry-audit-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-csp-minimal-bridge-smoke
        COMMAND s52_core_headless_csp_minimal_bridge_smoke
    )
    set_tests_properties(s52-core-headless-csp-minimal-bridge-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-feature-attribute-adapter-smoke
        COMMAND s52_core_headless_feature_attribute_adapter_smoke
    )
    set_tests_properties(s52-core-headless-feature-attribute-adapter-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-lookup-key-smoke
        COMMAND s52_core_headless_lookup_key_smoke
    )
    set_tests_properties(s52-core-headless-lookup-key-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-point-portrayal-selection-smoke
        COMMAND s52_core_headless_point_portrayal_selection_smoke
    )
    set_tests_properties(s52-core-headless-point-portrayal-selection-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-line-portrayal-selection-smoke
        COMMAND s52_core_headless_line_portrayal_selection_smoke
    )
    set_tests_properties(s52-core-headless-line-portrayal-selection-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-area-portrayal-selection-smoke
        COMMAND s52_core_headless_area_portrayal_selection_smoke
    )
    set_tests_properties(s52-core-headless-area-portrayal-selection-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-text-rule-selection-smoke
        COMMAND s52_core_headless_text_rule_selection_smoke
    )
    set_tests_properties(s52-core-headless-text-rule-selection-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-display-priority-selection-smoke
        COMMAND s52_core_headless_display_priority_selection_smoke
    )
    set_tests_properties(s52-core-headless-display-priority-selection-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-portrayal-ir-pipeline-smoke
        COMMAND s52_core_headless_portrayal_ir_pipeline_smoke
    )
    set_tests_properties(s52-core-headless-portrayal-ir-pipeline-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME s52-core-headless-rule-engine-smoke
        COMMAND s52_core_headless_rule_engine_smoke
    )
    set_tests_properties(s52-core-headless-rule-engine-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-instruction-ir-smoke
        COMMAND chart_runtime_instruction_ir_smoke
    )
    set_tests_properties(chart-runtime-instruction-ir-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-point-symbol-ir-smoke
        COMMAND chart_runtime_point_symbol_ir_smoke
    )
    set_tests_properties(chart-runtime-point-symbol-ir-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-line-style-ir-smoke
        COMMAND chart_runtime_line_style_ir_smoke
    )
    set_tests_properties(chart-runtime-line-style-ir-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-area-pattern-ir-smoke
        COMMAND chart_runtime_area_pattern_ir_smoke
    )
    set_tests_properties(chart-runtime-area-pattern-ir-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-area-renderer-smoke
        COMMAND chart_runtime_area_renderer_smoke
    )
    set_tests_properties(chart-runtime-area-renderer-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-text-rule-ir-smoke
        COMMAND chart_runtime_text_rule_ir_smoke
    )
    set_tests_properties(chart-runtime-text-rule-ir-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-text-layout-smoke
        COMMAND chart_runtime_text_layout_smoke
    )
    set_tests_properties(chart-runtime-text-layout-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-text-renderer-smoke
        COMMAND chart_runtime_text_renderer_smoke
    )
    set_tests_properties(chart-runtime-text-renderer-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-display-priority-ir-smoke
        COMMAND chart_runtime_display_priority_ir_smoke
    )
    set_tests_properties(chart-runtime-display-priority-ir-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-portrayal-ir-debug-dump-smoke
        COMMAND chart_runtime_portrayal_ir_debug_dump_smoke
    )
    set_tests_properties(chart-runtime-portrayal-ir-debug-dump-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-portrayal-ir-ingestion-smoke
        COMMAND chart_runtime_portrayal_ir_ingestion_smoke
    )
    set_tests_properties(chart-runtime-portrayal-ir-ingestion-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-priority-sorter-smoke
        COMMAND chart_runtime_priority_sorter_smoke
    )
    set_tests_properties(chart-runtime-priority-sorter-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-runtime-palette-colors-smoke
        COMMAND chart_runtime_runtime_palette_colors_smoke
    )
    set_tests_properties(chart-runtime-runtime-palette-colors-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-runtime-render-frame-smoke
        COMMAND chart_runtime_runtime_render_frame_smoke
    )
    set_tests_properties(chart-runtime-runtime-render-frame-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-point-symbol-atlas-loader-smoke
        COMMAND chart_runtime_point_symbol_atlas_loader_smoke
    )
    set_tests_properties(chart-runtime-point-symbol-atlas-loader-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-point-renderer-smoke
        COMMAND chart_runtime_point_renderer_smoke
    )
    set_tests_properties(chart-runtime-point-renderer-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-line-style-parser-smoke
        COMMAND chart_runtime_line_style_parser_smoke
    )
    set_tests_properties(chart-runtime-line-style-parser-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-line-renderer-smoke
        COMMAND chart_runtime_line_renderer_smoke
    )
    set_tests_properties(chart-runtime-line-renderer-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-open-chart-flow-smoke
        COMMAND chart_runtime_open_chart_flow_smoke
    )
    set_tests_properties(chart-runtime-open-chart-flow-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-runtime-s57-dataset-ingestion-smoke
        COMMAND
            "${CMAKE_COMMAND}" -E env
                "S57_TESTDATA_ROOT=$ENV{S57_TESTDATA_ROOT}"
                $<TARGET_FILE:chart_runtime_s57_dataset_ingestion_smoke>
    )
    set_tests_properties(chart-runtime-s57-dataset-ingestion-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        SKIP_RETURN_CODE 125
    )

    add_test(
        NAME chart-runtime-pattern-atlas-loader-smoke
        COMMAND chart_runtime_pattern_atlas_loader_smoke
    )
    set_tests_properties(chart-runtime-pattern-atlas-loader-smoke PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
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
        NAME regression-scene-policy-doc
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_REGRESSION_SCENE_POLICY_DOC:FILEPATH=${CMAKE_CURRENT_SOURCE_DIR}/docs/regression_scene_policy.md"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_regression_scene_policy.cmake"
    )

    add_test(
        NAME golden-image-harness-smoke
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_GOLDEN_NAME:STRING=golden-harness-self-check"
            "-DZERO_WX_GOLDEN_EXPECTED:FILEPATH=${CMAKE_CURRENT_SOURCE_DIR}/vendor/opencpn_s57data/rastersymbols-day.png"
            "-DZERO_WX_GOLDEN_ACTUAL:FILEPATH=${CMAKE_CURRENT_SOURCE_DIR}/vendor/opencpn_s57data/rastersymbols-day.png"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/compare_golden_image.cmake"
    )

    add_test(
        NAME zero-wx-source-verification
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_SOURCE_ROOT:PATH=${CMAKE_CURRENT_SOURCE_DIR}"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_zero_wx_source.cmake"
    )

    set(_zero_wx_build_verification_executables)
    if(TARGET chart_standalone)
        list(APPEND _zero_wx_build_verification_executables "$<TARGET_FILE:chart_standalone>")
    endif()
    if(TARGET chart_qt_host_widget_smoke)
        list(APPEND _zero_wx_build_verification_executables "$<TARGET_FILE:chart_qt_host_widget_smoke>")
    endif()

    add_test(
        NAME zero-wx-build-verification
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_SOURCE_ROOT:PATH=${CMAKE_CURRENT_SOURCE_DIR}"
            "-DZERO_WX_BUILD_ROOT:PATH=${CMAKE_BINARY_DIR}"
            "-DZERO_WX_EXECUTABLES:STRING=${_zero_wx_build_verification_executables}"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_zero_wx_build.cmake"
    )

    add_test(
        NAME api-cleanup-freeze
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_SOURCE_ROOT:PATH=${CMAKE_CURRENT_SOURCE_DIR}"
            "-DZERO_WX_PUBLIC_API_MANIFEST:FILEPATH=${CMAKE_CURRENT_SOURCE_DIR}/docs/public_api_freeze_manifest.txt"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_public_api_freeze.cmake"
    )

    add_test(
        NAME architecture-doc-final
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_ARCHITECTURE_FINAL_DOC:FILEPATH=${CMAKE_CURRENT_SOURCE_DIR}/docs/architecture_final.md"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_architecture_final_doc.cmake"
    )

    add_test(
        NAME migration-report-doc
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_MIGRATION_REPORT_DOC:FILEPATH=${CMAKE_CURRENT_SOURCE_DIR}/docs/migration_report.md"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_migration_report_doc.cmake"
    )

    add_test(
        NAME migration-complete-verification-doc
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_MIGRATION_COMPLETE_VERIFICATION_DOC:FILEPATH=${CMAKE_CURRENT_SOURCE_DIR}/docs/migration_complete_verification.md"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_migration_complete_verification_doc.cmake"
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

    add_test(
        NAME remove-wxglcontext-paths
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_SOURCE_ROOT:PATH=${CMAKE_CURRENT_SOURCE_DIR}"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_no_wxglcontext_paths.cmake"
    )

    add_test(
        NAME drop-old-host-canvas-path
        COMMAND
            "${CMAKE_COMMAND}"
            "-DZERO_WX_SOURCE_ROOT:PATH=${CMAKE_CURRENT_SOURCE_DIR}"
            -P
            "${CMAKE_CURRENT_SOURCE_DIR}/test/verify_no_old_host_canvas_paths.cmake"
    )
endif()
