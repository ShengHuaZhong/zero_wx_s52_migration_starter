# zero_wx_build_verification

## Objective

Provide an explicit build-layer gate that proves the project build configuration and produced runtime dependencies do not pull wx.

## Verification Inputs

- Source root (`CMakeLists.txt` and project CMake files).
- Build root (`CMakeCache.txt`, generated CMake files).
- Built host executables when available (`chart_standalone`, `chart_qt_host_widget_smoke`).

## Required Checks

- No `find_package(wxWidgets)` markers in project CMake inputs.
- No `wxWidgets`/`wxmsw`/`wxbase` markers in generated build CMake cache/config text.
- Runtime dependency list of built host executables contains no wx-named libraries.

## Execution

- CTest target: `zero-wx-build-verification`.
- Script: `test/verify_zero_wx_build.cmake`.

## Outcome

This gate validates build configuration and runtime linkage boundaries; source-token scanning remains handled by `zero-wx-source-verification`.
