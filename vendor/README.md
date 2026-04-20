# vendor

This directory is reserved for redistributable upstream data assets consumed by
the project at runtime.

## What belongs here

- XML, CSV, symbol, line, and pattern assets imported from an audited upstream
  snapshot
- Only the asset families explicitly allowed by provenance and license records

## What does not belong here

- Upstream source code
- Build outputs or generated caches
- Private or non-redistributable chart datasets
- Real ENC regression fixtures that should stay outside the public repository

## Current policy

- `vendor/opencpn_s57data/` is the reserved destination for the OpenCPN
  `data/s57data/` asset subset pinned in `third_party/provenance/opencpn.md`
- Vendored assets should keep upstream names unless a later task explicitly
  requires a project-owned manifest or index
- Real chart/test data must follow `docs/test_data_policy.md` and stay outside
  the redistributable vendor tree

## Related records

- `third_party/LICENSES/upstream-license-audit.md`
- `third_party/provenance/opencpn.md`
- `docs/test_data_policy.md`
