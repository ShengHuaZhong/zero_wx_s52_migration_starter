# AGENTS.md

## Mission

This repository rebuilds the useful S-52 portrayal capabilities historically found in OpenCPN `s52plib`,
but the final result must have **zero wxWidgets dependency**.

The target architecture is:

- `s52_core_headless`: zero-wx portrayal core
- `chart_runtime`: feature model, scene, IR, render orchestration
- `chart_qt_host`: Qt host layer only
- Qt6 + QRhi: the only rendering path

This project does **not** migrate OpenCPN UI, wx canvas, or wx/OpenGL host rendering.

---

## Hard architectural rules

1. Zero wx dependency is a hard requirement.
2. Do not include any `wx/*.h` header in project-owned code.
3. Do not expose any `wx` type in public headers.
4. Do not link any final binary or library against wxWidgets.
5. Do not port wx rendering into Qt.
6. Port only:
   - S-52 rules
   - S-52 lookup logic
   - conditional symbology logic
   - symbol/line/pattern/text selection logic
   - supporting assets and metadata
7. `chart_runtime` is the architectural center.
8. Qt host code must not own portrayal rules.
9. All renderer-facing data must be project-owned IR.
10. Vendored upstream material must stay isolated under `third_party/` and `vendor/`.

---

## Allowed and forbidden work

### Allowed
- vendoring upstream non-UI rule/asset code
- rewriting wx-dependent types into neutral project types
- replacing wx containers with STL
- replacing wx image/font/config paths with project-owned abstractions
- creating compatibility shims temporarily inside private modules
- building a headless S-52 core
- generating project-owned portrayal IR
- using Qt6 / QRhi for final rendering

### Forbidden
- introducing `wxWindow`, `wxDC`, `wxGCDC`, `wxGLContext`, `glChartCanvas`
- exposing OpenCPN internal types outside private compatibility modules
- making Qt widget code call old wx drawing paths
- making the host layer responsible for lookup, CSP, or portrayal decisions
- silently widening task scope

---

## Work policy

1. Work on exactly one task at a time.
2. Before changing code, summarize:
   - scope understood
   - touched layers
   - what will not change
3. Keep patches reviewable.
4. Prefer deletion of wx dependencies over wrapping them.
5. Stop at the first true blocker and write it to `state/blocked.md`.
6. After every task, update:
   - `state/current_iteration.md`
   - `state/done.md`
   - or `state/blocked.md`

---

## Required repository structure

- `third_party/`
- `vendor/`
- `include/`
- `src/`
- `docs/`
- `skills/`
- `tasks/`
- `state/`
- `test/`

---

## Layering rules

### s52_core_headless
Owns:
- S-52 asset loading
- lookup loading
- CSP execution
- symbol selection
- portrayal IR generation

Must not depend on:
- Qt Widgets
- wxWidgets
- windowing
- GPU API

### chart_runtime
Owns:
- feature model
- scene model
- viewport
- runtime API
- render orchestration

Must consume:
- project-owned portrayal IR only

### chart_qt_host
Owns:
- QWidget/QWindow host logic
- resize/input/event bridge
- present rendered result

Must not own:
- S-52 lookup logic
- CSP
- symbol selection

---

## Zero-wx acceptance rules

Migration is not complete unless all of the following are true:

1. `grep -R "wx/"` in project-owned source returns zero.
2. `grep -R "wxString"` in project-owned source returns zero.
3. public headers contain zero wx types.
4. CMake contains zero wxWidgets package dependency.
5. final binaries contain zero wx linkage.
6. portrayal path still works on real S57 fixtures.
7. host output is non-blank.
8. regression tests pass.

---

## Task execution order

Always follow this order:

1. provenance and licensing
2. asset vendoring
3. wx dependency audit
4. headless core extraction
5. neutral type replacement
6. lookup and CSP bridge
7. portrayal IR
8. renderer integration
9. host integration
10. regression and zero-wx verification
