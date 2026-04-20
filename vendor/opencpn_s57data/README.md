# opencpn_s57data

## Line styles

- In the pinned OpenCPN `5.12.4` snapshot, line-style assets live inside
  `chartsymbols.xml` under the `<line-styles>` section
- Task `016-import-line-assets` therefore relies on the already imported
  `vendor/opencpn_s57data/chartsymbols.xml` file as the upstream carrier for
  line-style data
- `S52RAZDS.RLE` is intentionally not imported by this task
