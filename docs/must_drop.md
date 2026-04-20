# must_drop.md

## 目标

本文件列出在当前迁移中必须整体丢弃的 wx 宿主路径。

判断标准：

- 它们以 `wxDC` / `wxGCDC` / `wxGLContext` / `glChartCanvas` 为核心入口
- 业务价值不在于“旧宿主实现方式”本身
- 按 `AGENTS.md` 规则，不允许把这些路径包装后继续主线使用

---

## 1. 必须丢弃的 whole-file 路径

- `libs/s52plib/src/s52plibGL.h`
- `libs/s52plib/src/Cs52_shaders.cpp`
- `libs/s52plib/src/Cs52_shaders.h`
- `libs/s52plib/src/s52shaders.cpp`
- `libs/s52plib/src/s52shaders.h`

原因：

- 这些文件的职责本身就是旧 GL / shader host 路径的一部分
- 最终架构要求 Qt6 / QRhi 成为唯一显示路径
- 因此它们不应进入 `s52_core_headless`

---

## 2. 必须丢弃的 function/path 族

### `libs/s52plib/src/s52plib.cpp` / `s52plib.h`

必须丢弃的旧宿主入口包括：

- `RenderObjectToDC`
- `RenderObjectToDCText`
- `RenderAreaToDC`
- `RenderObjectToGL`
- `RenderObjectToGLText`
- `RenderAreaToGL`
- `DoRenderObject`
- `DoRenderObjectTextOnly`
- `draw_lc_poly`
- `RenderText`
- `RenderFromHPGL::SetTargetDC`
- `RenderFromHPGL::SetTargetGCDC`
- `wxDC *m_pdc`
- `wxGLContext *m_glcc`
- `wxGCDC *targetGCDC`

这些入口都把旧 DC / GL host 直接暴露给规则层。

### `gui/include/gui/chartimg.h` / `gui/src/chartimg.cpp`

必须丢弃的旧宿主入口包括：

- `RenderRegionViewOnDC`
- `RenderRegionViewOnGL`
- `RenderViewOnDC`
- 各类 `wxMemoryDC` / `wxGLContext` 渲染签名
- 依赖 `wxBitmap` 的旧缩略图和 host 缓冲路径

### `gui/include/gui/s57chart.h` / `gui/src/s57chart.cpp`

必须丢弃的旧宿主入口包括：

- `RenderRegionViewOnDC`
- `RenderOverlayRegionViewOnDC`
- `RenderRegionViewOnDCNoText`
- `RenderRegionViewOnDCTextOnly`
- `RenderRegionViewOnGL`
- `RenderOverlayRegionViewOnGL`
- `RenderRegionViewOnGLNoText`
- `RenderViewOnGLTextOnly`
- `DoRenderRegionViewOnDC`
- `DoRenderRegionViewOnGL`
- `DoRenderOnGL`
- `DoRenderOnGLText`
- `DCRenderRect`
- `DCRenderLPB`
- `DCRenderText`
- `glChartCanvas::*` 的所有直接调用

这些路径体现的是旧 canvas / old host renderer，而不是可保留的 portrayal 决策逻辑。

### `gui/src/s57obj.cpp`

- `glChartCanvas.h` 相关路径必须丢弃

---

## 3. 为什么是“丢弃”而不是“重写”

- 这些路径的价值不在于算法，而在于旧宿主调用方式
- 新架构已经明确禁止继续保留：
  - `wxDC`
  - `wxGCDC`
  - `wxGLContext`
  - `glChartCanvas`
- 因而正确动作不是“把旧 host 包一层”，而是：
  - 抽取仍有价值的规则/数据逻辑
  - 让 renderer 只消费 project-owned IR
  - 用 Qt6 / QRhi 重建显示路径

---

## 4. 对后续任务的意义

- `028-headless-boundary-design` 需要把这些路径明确排除在 headless core 之外
- `038` 到 `041` 将按本清单逐步删除旧的 DC / GCDC / GLContext / canvas 路径
