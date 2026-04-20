find_package(
    Qt6GuiPrivate 6.8
    CONFIG
    REQUIRED
    PATHS "${Qt6_DIR}/../Qt6GuiPrivate" "$ENV{QT_ROOT}"
    PATH_SUFFIXES lib/cmake/Qt6GuiPrivate
)

add_library(chart_qt_host STATIC)
add_library(marine_chart::chart_qt_host ALIAS chart_qt_host)

target_sources(chart_qt_host
    PRIVATE
        chart_host_widget.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
        FILES
            "${PROJECT_SOURCE_DIR}/include/marine_chart/chart_qt_host/chart_host_widget.h"
)

target_compile_features(chart_qt_host PUBLIC cxx_std_20)

target_include_directories(chart_qt_host
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(chart_qt_host
    PUBLIC
        marine_chart::chart_runtime
        Qt6::Widgets
    PRIVATE
        Qt6::GuiPrivate
)

if(BUILD_TESTING)
    set(_zero_wx_qt_host_test_path "$<TARGET_FILE_DIR:Qt6::Core>;$ENV{PATH}")
    file(GLOB _zero_wx_vcpkg_debug_bins LIST_DIRECTORIES true "${PROJECT_SOURCE_DIR}/../vcpkg*/installed/x64-windows/debug/bin")
    foreach(_zero_wx_vcpkg_debug_bin IN LISTS _zero_wx_vcpkg_debug_bins)
        if(EXISTS "${_zero_wx_vcpkg_debug_bin}/zlibd1.dll" AND EXISTS "${_zero_wx_vcpkg_debug_bin}/zstd.dll")
            set(_zero_wx_qt_host_test_path "${_zero_wx_vcpkg_debug_bin};${_zero_wx_qt_host_test_path}")
            break()
        endif()
    endforeach()

    add_executable(chart_qt_host_widget_smoke
        "${PROJECT_SOURCE_DIR}/test/chart_qt_host_widget_smoke.cpp"
    )

    target_link_libraries(chart_qt_host_widget_smoke
        PRIVATE
            marine_chart::chart_qt_host
            marine_chart::chart_runtime
            marine_chart::s52_core_headless
            Qt6::Widgets
    )

    add_custom_command(
        TARGET chart_qt_host_widget_smoke POST_BUILD
        COMMAND
            "${CMAKE_COMMAND}" -E rm -f "$<TARGET_FILE_DIR:chart_qt_host_widget_smoke>/icuuc.dll"
        COMMAND
            "$<TARGET_FILE_DIR:Qt6::Core>/windeployqt.exe"
                --force
                --no-translations
                --dir "$<TARGET_FILE_DIR:chart_qt_host_widget_smoke>"
                "$<TARGET_FILE:chart_qt_host_widget_smoke>"
        COMMENT "Deploying Qt runtime for chart_qt_host_widget_smoke"
        VERBATIM
    )

    add_test(
        NAME chart-qt-host-widget-smoke
        COMMAND
            "${CMAKE_COMMAND}" -E env
                "PATH=${_zero_wx_qt_host_test_path}"
                "QT_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins"
                "QT_QPA_PLATFORM_PLUGIN_PATH=$<TARGET_FILE_DIR:Qt6::Core>/../plugins/platforms"
                "QT_QPA_PLATFORM=offscreen"
                $<TARGET_FILE:chart_qt_host_widget_smoke>
    )
    set_tests_properties(chart-qt-host-widget-smoke PROPERTIES
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    )
endif()
