# third_party

This directory is reserved for vendored upstream source code and the metadata
required to track it safely.

## What belongs here

- Upstream source code copied from a pinned provenance record
- Upstream license texts and audit notes under `third_party/LICENSES/`
- Provenance records under `third_party/provenance/`

## What does not belong here

- Project-owned implementation code
- Generated build outputs
- Real chart fixtures or other large runtime assets
- Any upstream payload without a matching provenance and license note

## Current policy

- `third_party/opencpn/` is the reserved destination for the audited OpenCPN
  code subset pinned in `third_party/provenance/opencpn.md`
- Vendored upstream files should remain as close to upstream layout as practical
- Any local modifications to vendored files must be traceable and reviewable

## Related records

- `third_party/LICENSES/upstream-license-audit.md`
- `third_party/provenance/opencpn.md`
