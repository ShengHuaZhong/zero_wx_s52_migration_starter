set(_zero_wx_chart_standalone_test_path "$<TARGET_FILE_DIR:Qt6::Core>;$ENV{PATH}")
file(GLOB _zero_wx_vcpkg_debug_bins LIST_DIRECTORIES true "${PROJECT_SOURCE_DIR}/../vcpkg*/installed/x64-windows/debug/bin")
foreach(_zero_wx_vcpkg_debug_bin IN LISTS _zero_wx_vcpkg_debug_bins)
    if(EXISTS "${_zero_wx_vcpkg_debug_bin}/zlibd1.dll" AND EXISTS "${_zero_wx_vcpkg_debug_bin}/zstd.dll")
        set(_zero_wx_chart_standalone_test_path "${_zero_wx_vcpkg_debug_bin};${_zero_wx_chart_standalone_test_path}")
        break()
    endif()
endforeach()

add_executable(chart_standalone
    chart_standalone_main.cpp
)

target_link_libraries(chart_standalone
    PRIVATE
        marine_chart::chart_qt_host
        marine_chart::chart_runtime
        marine_chart::s52_core_headless
        Qt6::Widgets
)

add_custom_command(
    TARGET chart_standalone POST_BUILD
    COMMAND
        "${CMAKE_COMMAND}" -E rm -f "$<TARGET_FILE_DIR:chart_standalone>/icuuc.dll"
    COMMAND
        "$<TARGET_FILE_DIR:Qt6::Core>/windeployqt.exe"
            --force
            --no-translations
            --dir "$<TARGET_FILE_DIR:chart_standalone>"
            "$<TARGET_FILE:chart_standalone>"
    COMMENT "Deploying Qt runtime for chart_standalone"
    VERBATIM
)

if(BUILD_TESTING)
    add_test(
        NAME chart-standalone-open-chart-smoke
        COMMAND
            "${CMAKE_COMMAND}" -E env
                "PATH=${_zero_wx_chart_standalone_test_path}"
                "QT_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins"
                "QT_QPA_PLATFORM_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins/platforms"
                "QT_QPA_PLATFORM=offscreen"
                "QT_SCALE_FACTOR=1"
                "QT_ENABLE_HIGHDPI_SCALING=0"
                $<TARGET_FILE:chart_standalone>
                --smoke-test
    )
    set_tests_properties(chart-standalone-open-chart-smoke PROPERTIES
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-standalone-non-blank-render-smoke
        COMMAND
            "${CMAKE_COMMAND}" -E env
                "PATH=${_zero_wx_chart_standalone_test_path}"
                "QT_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins"
                "QT_QPA_PLATFORM_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins/platforms"
                "QT_QPA_PLATFORM=windows"
                "QT_SCALE_FACTOR=1"
                "QT_ENABLE_HIGHDPI_SCALING=0"
                $<TARGET_FILE:chart_standalone>
                --non-blank-smoke
    )
    set_tests_properties(chart-standalone-non-blank-render-smoke PROPERTIES
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    )

    add_test(
        NAME chart-standalone-real-s57-smoke
        COMMAND
            "${CMAKE_COMMAND}" -E env
                "PATH=${_zero_wx_chart_standalone_test_path}"
                "QT_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins"
                "QT_QPA_PLATFORM_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins/platforms"
                "QT_QPA_PLATFORM=offscreen"
                "QT_SCALE_FACTOR=1"
                "QT_ENABLE_HIGHDPI_SCALING=0"
                "S57_TESTDATA_ROOT=$ENV{S57_TESTDATA_ROOT}"
                $<TARGET_FILE:chart_standalone>
                --real-s57-smoke
                "--s57-root=$ENV{S57_TESTDATA_ROOT}"
    )
    set_tests_properties(chart-standalone-real-s57-smoke PROPERTIES
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        SKIP_RETURN_CODE 125
    )

    set(_zero_wx_chart_standalone_golden_capture_path
        "${CMAKE_CURRENT_BINARY_DIR}/chart-standalone-golden-capture.png")
    add_test(
        NAME chart-standalone-golden-capture-smoke
        COMMAND
            "${CMAKE_COMMAND}" -E env
                "PATH=${_zero_wx_chart_standalone_test_path}"
                "QT_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins"
                "QT_QPA_PLATFORM_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins/platforms"
                "QT_QPA_PLATFORM=windows"
                "QT_SCALE_FACTOR=1"
                "QT_ENABLE_HIGHDPI_SCALING=0"
                $<TARGET_FILE:chart_standalone>
                --golden-capture
                "--capture-path=${_zero_wx_chart_standalone_golden_capture_path}"
    )
    set_tests_properties(chart-standalone-golden-capture-smoke PROPERTIES
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    )

    set(_zero_wx_scene01_actual_path "${CMAKE_CURRENT_BINARY_DIR}/scene-01-actual.png")
    add_test(
        NAME regression-scene-01
        COMMAND
            "${CMAKE_COMMAND}" -E env
                "PATH=${_zero_wx_chart_standalone_test_path}"
                "QT_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins"
                "QT_QPA_PLATFORM_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins/platforms"
                "QT_QPA_PLATFORM=windows"
                "QT_SCALE_FACTOR=1"
                "QT_ENABLE_HIGHDPI_SCALING=0"
                "S57_TESTDATA_ROOT=$ENV{S57_TESTDATA_ROOT}"
                powershell -NoProfile -ExecutionPolicy Bypass
                    -File "${PROJECT_SOURCE_DIR}/test/run_regression_scene.ps1"
                    -ChartExe "$<TARGET_FILE:chart_standalone>"
                    -SceneIndex 1
                    -GoldenImage "${PROJECT_SOURCE_DIR}/test/golden/scene-01.png"
                    -AssetRoot "${PROJECT_SOURCE_DIR}/vendor/opencpn_s57data"
                    -OutputImage "${_zero_wx_scene01_actual_path}"
    )
    set_tests_properties(regression-scene-01 PROPERTIES
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        SKIP_RETURN_CODE 125
    )

    set(_zero_wx_scene02_actual_path "${CMAKE_CURRENT_BINARY_DIR}/scene-02-actual.png")
    add_test(
        NAME regression-scene-02
        COMMAND
            "${CMAKE_COMMAND}" -E env
                "PATH=${_zero_wx_chart_standalone_test_path}"
                "QT_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins"
                "QT_QPA_PLATFORM_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins/platforms"
                "QT_QPA_PLATFORM=windows"
                "QT_SCALE_FACTOR=1"
                "QT_ENABLE_HIGHDPI_SCALING=0"
                "S57_TESTDATA_ROOT=$ENV{S57_TESTDATA_ROOT}"
                powershell -NoProfile -ExecutionPolicy Bypass
                    -File "${PROJECT_SOURCE_DIR}/test/run_regression_scene.ps1"
                    -ChartExe "$<TARGET_FILE:chart_standalone>"
                    -SceneIndex 2
                    -GoldenImage "${PROJECT_SOURCE_DIR}/test/golden/scene-02.png"
                    -AssetRoot "${PROJECT_SOURCE_DIR}/vendor/opencpn_s57data"
                    -OutputImage "${_zero_wx_scene02_actual_path}"
    )
    set_tests_properties(regression-scene-02 PROPERTIES
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        SKIP_RETURN_CODE 125
    )

    set(_zero_wx_scene03_actual_path "${CMAKE_CURRENT_BINARY_DIR}/scene-03-actual.png")
    add_test(
        NAME regression-scene-03
        COMMAND
            "${CMAKE_COMMAND}" -E env
                "PATH=${_zero_wx_chart_standalone_test_path}"
                "QT_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins"
                "QT_QPA_PLATFORM_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins/platforms"
                "QT_QPA_PLATFORM=windows"
                "QT_SCALE_FACTOR=1"
                "QT_ENABLE_HIGHDPI_SCALING=0"
                "S57_TESTDATA_ROOT=$ENV{S57_TESTDATA_ROOT}"
                powershell -NoProfile -ExecutionPolicy Bypass
                    -File "${PROJECT_SOURCE_DIR}/test/run_regression_scene.ps1"
                    -ChartExe "$<TARGET_FILE:chart_standalone>"
                    -SceneIndex 3
                    -GoldenImage "${PROJECT_SOURCE_DIR}/test/golden/scene-03.png"
                    -AssetRoot "${PROJECT_SOURCE_DIR}/vendor/opencpn_s57data"
                    -OutputImage "${_zero_wx_scene03_actual_path}"
    )
    set_tests_properties(regression-scene-03 PROPERTIES
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        SKIP_RETURN_CODE 125
    )
endif()
