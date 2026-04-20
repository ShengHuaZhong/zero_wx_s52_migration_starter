# Upstream License Audit

## Scope

This audit records the license posture and distribution boundaries for the
upstream material we expect to vendor later in this migration. It is a
license-only checkpoint for task `009`; exact source URLs, commits, and tags
remain for task `010`.

No upstream code or data has been imported into this repository yet beyond
directory placeholders.

## Audited upstream families

### 1. OpenCPN source code subset

- Intended destination: `third_party/opencpn/`
- Intended use: non-UI S-52 rule, lookup, CSP, and supporting portrayal code
- Official source: <https://github.com/OpenCPN/OpenCPN>
- License basis: the upstream `LICENSING` file states that OpenCPN is released
  under GNU GPL version 2 or, at the recipient's option, any later version

Distribution boundary:

- Only the non-UI, non-host subset needed for zero-wx migration may be vendored
- Imported code must stay isolated under `third_party/opencpn/`
- Project-owned code under `include/` and `src/` must not absorb upstream files
  without rewriting them into project-owned implementations
- Every imported file must keep a traceable license/provenance note before it is
  modified

### 2. OpenCPN `data/s57data` asset subset

- Intended destination: `vendor/opencpn_s57data/`
- Intended use: `chartsymbols.xml`, S-57 dictionaries, and symbol/line/pattern
  portrayal assets needed by the headless core
- Official source family: <https://github.com/OpenCPN/OpenCPN/tree/master/data>
- License basis: the upstream `data/copyright` file marks
  `data/s57data/*` and `data/s57data/raster_texture.*` as `GPL-2+`

Distribution boundary:

- Only the audited portrayal assets needed by later tasks may be copied into
  `vendor/opencpn_s57data/`
- Real ENC test data is not covered by this audit and must not be mixed into
  the vendored upstream asset directory
- Any external or private chart fixtures must follow
  `docs/test_data_policy.md` and stay outside the redistributable vendor tree

## Not cleared by this audit

- Any upstream file whose license has not been checked and recorded
- Any OpenCPN UI, wx host, or rendering-path code that violates `AGENTS.md`
- Any real chart/test dataset that is not clearly redistributable

## Required follow-up

- Task `010-upstream-provenance-record` must add exact source locations and
  commit/tag references for each vendored family
- Later import tasks must keep the final payload aligned with this audit and
  copy any required license text into `third_party/LICENSES/`

## Sources checked for task 009

- OpenCPN repository landing page:
  <https://github.com/OpenCPN/OpenCPN>
- OpenCPN `LICENSING` file:
  <https://github.com/OpenCPN/OpenCPN/blob/master/LICENSING>
- OpenCPN `data/copyright` file:
  <https://raw.githubusercontent.com/OpenCPN/OpenCPN/master/data/copyright>
