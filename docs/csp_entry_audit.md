# csp_entry_audit.md

## Scope

This audit records the conditional symbology procedure entry names referenced by
`CS(...)` calls in the vendored `vendor/opencpn_s57data/chartsymbols.xml`
lookup instructions.

## Current entry set

The pinned OpenCPN `5.12.4` / `Release_5.12.4` snapshot currently references
22 unique CSP entry names:

- `CLRLIN01`: 1
- `DATCVR01`: 4
- `DEPARE01`: 4
- `DEPARE02`: 4
- `DEPCNT02`: 2
- `LEGLIN02`: 1
- `LIGHTS05`: 6
- `OBSTRN04`: 11
- `OWNSHP02`: 2
- `PASTRK01`: 1
- `QUAPOS01`: 4
- `RESARE01`: 1
- `RESARE02`: 7
- `RESTRN01`: 67
- `SLCONS03`: 12
- `SOUNDG02`: 2
- `SYMINS01`: 5
- `TOPMAR01`: 53
- `TOPMARI1`: 1
- `VESSEL01`: 2
- `VRMEBL01`: 2
- `WRECKS02`: 4

## Notes

- This file audits the entry-name inventory only; it does not execute CSP logic.
- `RESTRN01` and `TOPMAR01` are the most frequent entrypoints in the current
  snapshot.
- Bridging or implementing CSP execution remains the responsibility of later
  tasks.
