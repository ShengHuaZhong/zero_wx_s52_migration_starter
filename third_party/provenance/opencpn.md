# OpenCPN Provenance Record

## Snapshot selection

- Checked on: `2026-04-20`
- Upstream repository: <https://github.com/OpenCPN/OpenCPN>
- Selected upstream release: `OpenCPN 5.12.4`
- Selected tag: `Release_5.12.4`
- Selected commit: `37fd0cddb7334fe489e9f18aa163977a9c5c84f7`
- Release page:
  <https://github.com/OpenCPN/OpenCPN/releases/tag/Release_5.12.4>

Why this snapshot:

- It is the latest published OpenCPN release checked for task `010`
- It gives one pinned baseline for both the rule/lookup code family and the
  `data/s57data` asset family
- Later import tasks can reference this exact snapshot without relying on the
  moving `master` branch

## Planned vendored families

### 1. OpenCPN code subset

- Local destination: `third_party/opencpn/`
- Upstream source root: `OpenCPN/OpenCPN`
- Upstream path scope: exact files to be enumerated by later audit/import tasks;
  intended scope is limited to the non-UI S-52 rule, lookup, CSP, and portrayal
  support code
- Version pin for all future imports in this family:
  - Tag: `Release_5.12.4`
  - Commit: `37fd0cddb7334fe489e9f18aa163977a9c5c84f7`

### 2. OpenCPN `s57data` asset subset

- Local destination: `vendor/opencpn_s57data/`
- Upstream source root: `OpenCPN/OpenCPN`
- Upstream path scope: `data/s57data/`
- Version pin for all future imports in this family:
  - Tag: `Release_5.12.4`
  - Commit: `37fd0cddb7334fe489e9f18aa163977a9c5c84f7`

## Current repository state

- Imported from this snapshot so far:
  - `vendor/opencpn_s57data/chartsymbols.xml`
  - `vendor/opencpn_s57data/s57attributes.csv`
  - `vendor/opencpn_s57data/s57objectclasses.csv`
  - `vendor/opencpn_s57data/rastersymbols-day.png`
  - `vendor/opencpn_s57data/rastersymbols-dusk.png`
  - `vendor/opencpn_s57data/rastersymbols-dark.png`
- This record only establishes the source, version, and commit/tag boundary
- Any future vendored payload must remain consistent with
  `third_party/LICENSES/upstream-license-audit.md`

## Follow-up expectations

- Task `011-vendor-layout` should keep these families isolated in their planned
  local destinations
- Tasks `012` through `017` should use this record when importing concrete asset
  files
- Tasks `020` and later should use this record when auditing and importing code
  files from the pinned OpenCPN snapshot
