# wxglcontext_path_removal.md

## 目标

记录并冻结 project-owned 源码中对 `wxGLContext` 路径的删除状态。

当前仓库没有从旧 wx/OpenGL host 直接搬运实现，因此这一步的主要动作是：

- 确认 project-owned `include/` 与 `src/` 中已经没有 `wxGLContext` 路径
- 对旧 GL host 入口建立专项 smoke guard
- 保证这些入口只留在 `must_drop` / 审计文档中作为禁止回流的记录

---

## 当前状态

在 project-owned `include/` 与 `src/` 中，以下旧 `wxGLContext` 路径当前都必须保持为零：

- `wxGLContext`
- `RenderObjectToGL`
- `RenderObjectToGLText`
- `RenderAreaToGL`
- `RenderRegionViewOnGL`
- `RenderOverlayRegionViewOnGL`
- `RenderRegionViewOnGLNoText`
- `RenderViewOnGLTextOnly`
- `DoRenderOnGL`
- `DoRenderOnGLText`
- `m_glcc`

这些名称允许只出现在：

- `docs/must_drop.md`
- 审计文档
- 针对禁用词的测试脚本

它们不得重新进入 project-owned 头文件、源文件或可编译接口。

---

## 与上游分类的关系

- `docs/must_drop.md` 已经把 `wxGLContext` 宿主路径标成必须丢弃
- `040-remove-wxglcontext-paths` 在当前仓库状态下的完成标准，是：
  - project-owned 源码里零 `wxGLContext` 路径
  - 有专项 smoke 阻止这些入口回流

---

## 对后续任务的约束

- `041` 不得通过旧 canvas 包装把任何 `Render*OnGL` / `DoRenderOnGL*` 入口带回主线
- 后续 Qt6 / QRhi 任务必须通过新的 host / runtime / IR 路径实现显示，而不是恢复旧 GL host 语义
