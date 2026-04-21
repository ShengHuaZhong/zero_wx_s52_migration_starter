# architecture_final

## Final Layering

### `s52_core_headless`

- Owns S-52 asset loading, lookup/csp bridge, and feature-to-portrayal selection primitives.
- Produces project-owned portrayal IR inputs and does not depend on Qt Widgets, wx, or GPU APIs.

### `chart_runtime`

- Remains the architectural center.
- Owns portrayal IR ingestion, palette/runtime models, render-frame orchestration, and S57 dataset feature ingestion for host-facing open flow.
- Exposes project-owned runtime data only (no Qt types in runtime/headless public API).

### `chart_qt_host` / `chart_standalone`

- Own host/container bridge only.
- Perform Qt6/QRhi presentation, host lifecycle, and framebuffer capture for smoke/regression.
- Do not own lookup/CSP/rule decisions.

## Rendering Path

- Single rendering host path: Qt 6 + QRhi (`QRhiWidget` in `ChartHostWidget`).
- Host output is validated by non-blank smoke and golden-regression scenes.

## Real-S57 and Regression

- Real external ENC fixtures are consumed through `S57_TESTDATA_ROOT`.
- Real-S57 smoke is exercised by standalone host (`chart-standalone-real-s57-smoke`).
- Golden regression scenes are covered by `regression-scene-01/02/03`.

## Zero-wx Enforcement

- Source-level guard: `zero-wx-source-verification`.
- Build/runtime guard: `zero-wx-build-verification`.
- Rule-freeze and legacy-path guards remain active (`zero-wx-rule-freeze`, `remove-wxdc-paths`, etc.).

## Public API Freeze

- Current public header surface is frozen by `docs/public_api_freeze_manifest.txt`.
- API drift and non-host Qt leakage are blocked by `api-cleanup-freeze`.

## Phase-G Completion Boundary

- Real S57 host smoke: done.
- Golden harness + 3 baseline scenes: done.
- Zero-wx source/build verification: done.
- Public API freeze + final architecture doc: done.
