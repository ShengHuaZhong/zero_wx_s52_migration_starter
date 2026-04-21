# migration_report

## Summary

The repository migration reached phase-G completion targets for the scoped roadmap:

- real-S57 host smoke path
- golden-image harness with three regression scenes
- zero-wx source/build verification gates
- public API freeze and final architecture consolidation

## Delivered Outcomes

- `chart_runtime` now ingests real external S57 dataset records into project-owned `RuleLayerFeature` inputs for host smoke/regression.
- `chart_standalone` supports real-S57 smoke and golden framebuffer capture.
- Regression scenes `scene-01/02/03` are captured from real ENC cells and validated against committed golden baselines.
- Dedicated source and build verification tests enforce zero-wx constraints.
- Public API surface is frozen via manifest and freeze gate.

## Architectural Conformance

- DLL-first/module boundaries remain centered on `chart_runtime`.
- Qt Widgets remains shell/container/presentation only (`chart_qt_host`, `chart_standalone`).
- Rendering host path remains Qt 6 + QRhi.
- Runtime/headless public APIs remain project-owned and wx-free.

## Verification Evidence

- Real-S57 smoke: `chart-runtime-s57-dataset-ingestion-smoke`, `chart-standalone-real-s57-smoke`.
- Golden harness: `golden-image-harness-smoke`, `chart-standalone-golden-capture-smoke`.
- Regression scenes: `regression-scene-01`, `regression-scene-02`, `regression-scene-03`.
- Zero-wx gates: `zero-wx-source-verification`, `zero-wx-build-verification`, `zero-wx-rule-freeze`.
- API freeze: `api-cleanup-freeze`.

## Known Limits / Residual Risk

- Current real-S57 ingestion for smoke/regression extracts feature identity (`FRID`/`OBJL`/`PRIM`) and does not yet implement full geometry/attribute decoding.
- Golden comparison currently uses deterministic image digest matching; no tolerance-based comparator is introduced.

## Conclusion

Within the scoped tasks and architecture constraints, migration goals were met with zero-wx enforcement, real-S57 host smoke coverage, and repeatable regression verification.
