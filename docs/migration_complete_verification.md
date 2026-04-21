# migration_complete_verification

## Final Acceptance Checklist

1. `chartsymbols.xml` / `s57attributes.csv` / `s57objectclasses.csv` load path is available and verified by smoke tests.
2. `S57 feature -> S52 lookup/CSP bridge -> portrayal IR` flow is exercised through runtime open-chart and rule-engine smoke coverage.
3. Qt 6 + QRhi is the active host rendering path (`ChartHostWidget` via `QRhiWidget`).
4. Runtime/headless public API remains free of wx and non-host Qt leakage.
5. CMake/build configuration remains free of wx dependency markers.
6. Runtime dependency verification reports no wx-linked host binaries.
7. Real-S57 host smoke and golden regression scenes (`scene-01/02/03`) pass with external test data.
8. Regression and policy/freeze verification tests pass under the configured debug preset.

## Final Verification Command Set

- `cmake --preset windows-msvc-debug`
- `cmake --build --preset build-windows-msvc-debug --parallel`
- `ctest --preset test-windows-msvc-debug --output-on-failure`

## Result

Final acceptance is based on the full preset run above combined with dedicated phase-G gates:

- real-S57 smoke
- golden harness + scene regressions
- zero-wx source/build verification
- API freeze
- architecture/report doc guards
