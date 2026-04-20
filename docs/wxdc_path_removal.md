# wxdc_path_removal.md

## 目标

记录并冻结 project-owned 源码中对 `wxDC` 绘制接口的删除状态。

当前仓库的 `s52_core_headless` 是从零 wx 骨架开始建立的，因此这一步的主要动作
不是“从现有 project-owned 代码中删掉大量 `wxDC` 实现”，而是：

- 明确当前 `include/` 与 `src/` 中已经没有 `wxDC` 路径
- 对这些旧 DC 绘制入口建立专项 smoke guard
- 把上游必须丢弃的 DC 路径继续限定在文档与审计范围

---

## 当前状态

在 project-owned `include/` 与 `src/` 中，以下旧 DC 路径当前都必须保持为零：

- `wxDC`
- `wxMemoryDC`
- `RenderObjectToDC`
- `RenderObjectToDCText`
- `RenderAreaToDC`
- `RenderRegionViewOnDC`
- `RenderOverlayRegionViewOnDC`
- `RenderViewOnDC`
- `DCRenderRect`
- `DCRenderLPB`
- `DCRenderText`
- `RenderFromHPGL::SetTargetDC`

这些名称仍可能出现在：

- `docs/must_drop.md`
- 审计文档
- 针对禁用词的测试脚本

它们不得重新进入 project-owned 头文件、源文件或可编译接口。

---

## 与上游分类的关系

- `docs/must_drop.md` 已经把旧 `wxDC` 宿主入口标成“必须丢弃”
- `038-remove-wxdc-paths` 在当前仓库状态下的完成标准，是：
  - project-owned 源码里零 `wxDC` 绘制接口
  - 有专项 smoke 持续阻止这些入口回流

---

## 对后续任务的约束

- `039` 不得通过 `wxGCDC` 重新引回 DC 路径
- `040` 不得通过 `wxGLContext` 保留旧 host 渲染入口
- `041` 不得通过旧 canvas 包装恢复 `glChartCanvas` 风格调用
