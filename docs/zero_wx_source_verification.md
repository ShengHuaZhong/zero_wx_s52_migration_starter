# zero_wx_source_verification

## Objective

Provide an explicit source-level verification gate that enforces zero wx tokens in project-owned code.

## Verification Scope

- `include/`
- `src/`
- `apps/`
- `test/`

Vendored trees (`third_party/`, `vendor/`) are intentionally out of scope for this source-level gate.

## Required Checks

- No `wx/` include path markers in project-owned source.
- No `wxString` markers in project-owned source.
- No public-header wx value or host types (`wxColour`, `wxBitmap`, `wxDC`, `wxWindow`, etc.).
- No legacy host markers (`glChartCanvas`) in project-owned source.

## Execution

- CTest target: `zero-wx-source-verification`.
- Script: `test/verify_zero_wx_source.cmake`.

## Outcome

This gate verifies source conformance only; build-system and binary linkage checks are covered by later tasks.
