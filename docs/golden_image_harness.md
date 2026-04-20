# golden_image_harness

## Objective

Provide a minimal, deterministic golden-image harness that can be reused by scene regression tasks.

## Capture Entry

- `chart_standalone` supports `--golden-capture --capture-path=<output-file>`.
- Capture runs through the existing runtime + host pipeline (no special renderer bypass).
- Capture can run with demo inputs or real-S57 smoke inputs.

## Compare Entry

- `test/compare_golden_image.cmake` compares expected and actual image files by SHA256 digest.
- Required CMake variables:
  - `ZERO_WX_GOLDEN_EXPECTED`
  - `ZERO_WX_GOLDEN_ACTUAL`
- Optional variable:
  - `ZERO_WX_GOLDEN_NAME`

## Gating Rules

- Missing expected or actual file is a hard failure.
- Digest mismatch is a hard failure.
- External real-S57 data requirements continue to use `S57_TESTDATA_ROOT` skip gating where applicable.

## Ownership Boundary

- `chart_runtime`: build portrayal + render frame.
- `chart_qt_host` / `chart_standalone`: host rendering and framebuffer capture bridge.
- Harness does not introduce wx paths and does not widen portrayal ownership into host code.
