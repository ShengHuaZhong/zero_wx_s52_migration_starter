# api_cleanup_freeze

## Objective

Freeze the current public C++ API surface so follow-up work does not silently widen ABI or leak host-framework types.

## Freeze Inputs

- Public header manifest: `docs/public_api_freeze_manifest.txt`
- Public header root: `include/marine_chart/`

## Freeze Rules

- Public header file set must match the manifest exactly.
- Public headers must not introduce Qt type leakage (`QWidget`, `QString`, `QImage`, `QRhi`, etc.).
- Public headers must remain wx-free.
- Any intentional API change must update the manifest and corresponding freeze checks in the same task.

## Verification

- CTest target: `api-cleanup-freeze`.
- Script: `test/verify_public_api_freeze.cmake`.

## Notes

- This freeze tracks API shape and host-type boundaries, not behavioral correctness.
