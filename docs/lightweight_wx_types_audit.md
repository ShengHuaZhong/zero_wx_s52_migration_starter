# lightweight_wx_types_audit.md

## 目标

本文件审计当前候选迁移文件集合中的“轻量 wx 值类型”依赖。

本次统计使用大小写敏感匹配，避免把局部变量名误算成类型名。

审计范围内的目标类型为：

- `wxString`
- `wxColour`
- `wxColor`
- `wxPoint`
- `wxRect`
- `wxSize`
- `wxRealPoint`
- `wxPoint2DDouble`

---

## 1. 总量结果

- 有轻量类型命中的文件数：`19`
- 无轻量类型命中的文件数：`8`
- 总命中条数：`899`

这说明当前 S-52 相关代码并不只是“include 依赖 wx”，而是深度依赖 wx 的值语义类型。

---

## 2. 按类型统计

- `wxString`: `567`
- `wxPoint`: `130`
- `wxRect`: `88`
- `wxColour`: `39`
- `wxPoint2DDouble`: `36`
- `wxColor`: `30`
- `wxSize`: `8`
- `wxRealPoint`: `1`

直接结论：

- `wxString` 是最主要的迁移阻力之一
- `wxPoint` / `wxRect` / `wxSize` 已经构成明显的几何类型替换需求
- `wxColour` / `wxColor` 同时存在，后续颜色类型清理需要兼顾两种拼写

---

## 3. 命中最重的文件

- `libs/s52plib/src/s52plib.cpp`: `230`
- `gui/src/s57chart.cpp`: `213`
- `libs/s52plib/src/s52cnsy.cpp`: `123`
- `gui/src/chartimg.cpp`: `117`
- `libs/s52plib/src/s52plib.h`: `46`
- `libs/s52plib/src/chartsymbols.cpp`: `38`
- `gui/include/gui/s57chart.h`: `31`
- `libs/s52plib/src/chartsymbols.h`: `29`
- `gui/include/gui/chartimg.h`: `22`

这批文件将是后续 neutral type replacement 与 headless 切边的重点区域。

---

## 4. 当前未命中轻量值类型的候选文件

以下候选文件在本次轻量类型审计中没有命中：

- `libs/s52plib/src/Cs52_shaders.cpp`
- `libs/s52plib/src/Cs52_shaders.h`
- `libs/s52plib/src/s52plibGL.h`
- `libs/s52plib/src/s52shaders.cpp`
- `libs/s52plib/src/s52shaders.h`
- `libs/s52plib/src/s52utils.cpp`
- `libs/s52plib/src/s52utils.h`
- `libs/s57-charts/src/ogrs57datasource.cpp`

注意：

- “未命中轻量值类型”不代表没有其他 wx 依赖
- 这些文件仍需接受资源层和 UI/host 层审计

---

## 5. 对后续任务的意义

- `023` 将继续把 `wxImage` / `wxBitmap` / `wxFont` / `wxFileConfig` 这类资源层依赖单独拎出来
- `024` 将继续把 `wxDC` / `wxGCDC` / `wxGLContext` / `wxWindow` 这类宿主与绘制依赖单独拎出来
- `031` 到 `037` 的 neutral type tasks 可以直接把本清单当作替换压力图
