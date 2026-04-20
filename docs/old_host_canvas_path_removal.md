# old_host_canvas_path_removal.md

## 目标

记录并冻结 project-owned 源码中对旧 canvas 宿主路径的切断状态。

当前仓库没有从历史 `chartimg` / `s57chart` / `glChartCanvas` 路径直接搬运实现，
因此这一步的主要动作是：

- 确认 project-owned `include/` 与 `src/` 中已经没有旧 canvas host 路径
- 对旧 canvas host 入口建立专项 smoke guard
- 保证这些入口只留在 `must_drop` / 审计文档中作为禁止回流的记录

---

## 当前状态

在 project-owned `include/` 与 `src/` 中，以下旧 canvas host 路径当前都必须保持为零：

- `glChartCanvas`
- `RenderRegionViewOnDC`
- `RenderOverlayRegionViewOnDC`
- `RenderRegionViewOnDCNoText`
- `RenderRegionViewOnDCTextOnly`
- `RenderRegionViewOnGL`
- `RenderOverlayRegionViewOnGL`
- `RenderRegionViewOnGLNoText`
- `RenderViewOnDC`
- `RenderViewOnGLTextOnly`
- `DoRenderRegionViewOnDC`
- `DoRenderRegionViewOnGL`
- `DoRenderOnGL`
- `DoRenderOnGLText`

这些名称允许只出现在：

- `docs/must_drop.md`
- 审计文档
- 针对禁用词的测试脚本

它们不得重新进入 project-owned 头文件、源文件或可编译接口。

---

## 与上游分类的关系

- `docs/must_drop.md` 已经把旧 canvas host 路径标成必须丢弃
- `041-drop-old-host-canvas-path` 在当前仓库状态下的完成标准，是：
  - project-owned 源码里零旧 canvas host 路径
  - 有专项 smoke 阻止这些入口回流

---

## 对后续任务的约束

- `042` 之后的资产、lookup、IR、runtime 和 host 任务都不得通过旧 canvas 命名或 调用形态恢复历史宿主
- 任何显示路径都必须沿着 `chart_runtime -> project-owned IR -> Qt6 / QRhi host` 前进
