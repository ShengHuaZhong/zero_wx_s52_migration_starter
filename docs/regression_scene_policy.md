# regression_scene_policy

## Objective

Freeze the minimal regression-scene policy for phase G so upcoming golden-image tasks can reuse one stable contract.

## Dataset Contract

- External real S57 fixtures are provided by `S57_TESTDATA_ROOT`.
- Regression scenes never hardcode developer-specific absolute paths in source code.
- When `S57_TESTDATA_ROOT` is missing, scene-based tests must skip through the existing external-testdata gating path.

## Scene Selection

- `scene-01`: first available ENC cell under `S57_TESTDATA_ROOT` (stable alphabetical order).
- `scene-02`: second available ENC cell under `S57_TESTDATA_ROOT`.
- `scene-03`: third available ENC cell under `S57_TESTDATA_ROOT`.

Only `.000`/`.00x` ENC cell files are in scope for scene selection.

## Rendering Contract

- Scene capture uses `chart_standalone` host shell in offscreen mode.
- Scene capture must run through the same `chart_runtime` open-chart/render-frame flow used by smoke tests.
- Regression capture must remain Qt Widgets shell + Qt 6 RHI based; no wx render path is allowed.

## Golden Policy

- Golden baselines are checked into repository-owned test assets.
- Scene output naming is deterministic (`scene-01`, `scene-02`, `scene-03`).
- Golden comparison starts with deterministic image digest comparison before any future pixel-threshold extension.

## Failure/Skip Rules

- Missing `S57_TESTDATA_ROOT` -> skip scene/golden tests (not fake pass).
- Missing scene input file for configured scene id -> fail the corresponding scene test.
- Generated output identical to blank host clear-frame snapshot -> fail.

## Ownership Boundary

- `chart_runtime` owns scene feature ingestion and render-frame generation.
- `chart_qt_host` / `chart_standalone` own host/container/capture bridge only.
- This policy does not widen scope into UI migration or wx compatibility work.
