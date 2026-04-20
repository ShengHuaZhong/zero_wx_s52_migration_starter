# wx_include_audit.md

## 目标

本文件统计 OpenCPN `Release_5.12.4` / commit
`37fd0cddb7334fe489e9f18aa163977a9c5c84f7` 中，当前候选迁移文件集合里的
`wx/*.h` / `wx/*.cpp` include 命中情况。

该清单只做“统计与定位”，不在本任务中下迁移分类结论。

---

## 1. 审计范围

本次统计覆盖 `docs/s52_file_inventory.md` 中列出的 27 个候选文件：

- `libs/s52plib/src/*`
- `gui/include/gui/S57ObjectDesc.h`
- `gui/include/gui/chartimg.h`
- `gui/include/gui/s57chart.h`
- `gui/src/chartimg.cpp`
- `gui/src/s57chart.cpp`
- `gui/src/s57obj.cpp`
- `libs/s57-charts/src/ogrs57datasource.cpp`

---

## 2. 总量结果

- 有 `wx/*` include 命中的文件数：`17`
- 无 `wx/*` include 命中的文件数：`10`
- 总命中条数：`63`

这说明当前候选集合并不是“少量 wx 污染”，而是系统性依赖。

---

## 3. 按文件统计

命中数最多的文件如下：

- `gui/src/s57chart.cpp`: `10`
- `gui/src/chartimg.cpp`: `9`
- `libs/s52plib/src/s52plib.cpp`: `7`
- `gui/include/gui/s57chart.h`: `6`
- `gui/src/s57obj.cpp`: `6`
- `libs/s52plib/src/chartsymbols.cpp`: `4`
- `libs/s52plib/src/mygeom.cpp`: `4`

其他有命中的文件：

- `libs/s52plib/src/Cs52_shaders.h`: `2`
- `libs/s52plib/src/DepthFont.cpp`: `1`
- `libs/s52plib/src/DepthFont.h`: `1`
- `libs/s52plib/src/mygeom.h`: `2`
- `libs/s52plib/src/s52cnsy.cpp`: `3`
- `libs/s52plib/src/s52plib.h`: `2`
- `libs/s52plib/src/s52utils.h`: `2`
- `libs/s52plib/src/TexFont.cpp`: `1`
- `libs/s52plib/src/TexFont.h`: `2`
- `gui/include/gui/S57ObjectDesc.h`: `1`

---

## 4. 按头文件统计

命中次数最多的 `wx/*` include 为：

- `wx/wx.h`: `12`
- `wx/wxprec.h`: `10`
- `wx/tokenzr.h`: `6`
- `wx/image.h`: `4`
- `wx/filename.h`: `4`
- `wx/wfstream.h`: `3`
- `wx/arrimpl.cpp`: `3`

其余仍在候选集合中出现的头包括：

- `wx/msw/msvcrt.h`
- `wx/dir.h`
- `wx/textfile.h`
- `wx/stream.h`
- `wx/font.h`
- `wx/fileconf.h`
- `wx/listimpl.cpp`
- `wx/glcanvas.h`
- `wx/dynarray.h`
- `wx/mstream.h`
- `wx/hashmap.h`
- `wx/dcgraph.h`
- `wx/string.h`
- `wx/colour.h`

---

## 5. 当前无 `wx/*` include 命中的文件

以下候选文件在本次 include 统计中未直接命中 `wx/*`：

- `libs/s52plib/src/chartsymbols.h`
- `libs/s52plib/src/color_types.h`
- `libs/s52plib/src/Cs52_shaders.cpp`
- `libs/s52plib/src/s52plibGL.h`
- `libs/s52plib/src/s52s57.h`
- `libs/s52plib/src/s52shaders.cpp`
- `libs/s52plib/src/s52shaders.h`
- `libs/s52plib/src/s52utils.cpp`
- `gui/include/gui/chartimg.h`
- `libs/s57-charts/src/ogrs57datasource.cpp`

注意：

- “无 `wx/*` include”不等于“可直接迁移”
- 这些文件仍可能通过间接类型、宏、宿主调用链等方式带入 wx 依赖

---

## 6. 对后续任务的意义

- `022` 将继续审计轻量 wx 类型，如 `wxString`、`wxColour`、`wxPoint` 等
- `023` 将把资源层依赖单独拎出来，例如 `wxImage`、`wxFont`、`wxFileConfig`
- `024` 将把 UI / 绘制 / host 依赖单独拎出来，例如 `wxDC`、`wxGCDC`、
  `wxGLContext`、`wxWindow`
