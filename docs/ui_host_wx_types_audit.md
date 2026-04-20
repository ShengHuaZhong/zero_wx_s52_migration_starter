# ui_host_wx_types_audit.md

## 目标

本文件审计候选迁移文件集合中的 UI / 绘制宿主 wx 类型依赖。

本次聚焦的类型为：

- `wxDC`
- `wxMemoryDC`
- `wxGCDC`
- `wxGLContext`
- `wxGLCanvas`
- `wxWindow`
- `glChartCanvas`

这些类型直接决定哪些路径必须留在旧宿主语义里，哪些路径不能进入最终
`s52_core_headless`。

---

## 1. 总量结果

- 有 UI / host 类型命中的文件数：`9`
- 总命中条数：`121`

按类型统计：

- `wxMemoryDC`: `48`
- `wxGLContext`: `30`
- `wxDC`: `27`
- `glChartCanvas`: `8`
- `wxGCDC`: `8`

本次未命中：

- `wxGLCanvas`
- `wxWindow`
- `wxClientDC`
- `wxPaintDC`

---

## 2. 命中最重的文件

- `libs/s52plib/src/s52plib.cpp`: `37`
- `gui/src/s57chart.cpp`: `32`
- `gui/include/gui/s57chart.h`: `17`
- `libs/s52plib/src/s52plib.h`: `17`
- `gui/include/gui/chartimg.h`: `9`
- `gui/src/chartimg.cpp`: `6`

这说明旧的宿主/绘制耦合并不只存在于 GUI 文件里，`s52plib` 本体也直接暴露了
`wxDC` / `wxGLContext` 双通道。

---

## 3. 依赖形态观察

### `wxDC` / `wxMemoryDC` / `wxGCDC`

- `s52plib.cpp` 直接实现 `RenderObjectToDC`、`RenderAreaToDC`、`RenderText`
  等 DC 路径
- `s57chart.cpp` / `chartimg.h` / `s57chart.h` 仍然把 `wxMemoryDC` 作为 host
  渲染入口
- `wxGCDC` 仍被用于 alpha / antialias 相关分支

### `wxGLContext`

- `s52plib.cpp` / `s52plib.h` 暴露了 `RenderObjectToGL`、`RenderAreaToGL`、
  `RenderObjectToGLText` 等接口
- `s57chart.h` / `chartimg.h` / `s57chart.cpp` 也保留了 GL host 入口

### `glChartCanvas`

- `s57chart.cpp` / `s57obj.cpp` 仍然直接依赖旧 canvas 路径
- 这是后续必须彻底丢弃的宿主路径之一

---

## 4. 对后续任务的意义

- `025` 到 `027` 的分类任务可以直接把这批命中作为“不可直接 headless 化”的强信号
- `038-remove-wxdc-paths`
- `039-remove-wxgcdc-paths`
- `040-remove-wxglcontext-paths`
- `041-drop-old-host-canvas-path`

以上任务的切入点已经在本清单中明确定位
