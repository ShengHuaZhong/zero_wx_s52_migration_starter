# wxgcdc_path_removal.md

## 目标

记录并冻结 project-owned 源码中对 `wxGCDC` 路径的删除状态。

当前仓库的 `s52_core_headless` 没有从旧 wx host 实现直接搬运代码，因此这一步的
完成方式是：

- 确认 project-owned `include/` 与 `src/` 中已经没有 `wxGCDC` 路径
- 为 `wxGCDC` 相关宿主入口建立专项 smoke guard
- 保证这些入口只留在 `must_drop` / 审计文档中作为“禁止回流”的记录

---

## 当前状态

在 project-owned `include/` 与 `src/` 中，以下旧 `wxGCDC` 路径当前都必须保持为零：

- `wxGCDC`
- `RenderFromHPGL::SetTargetGCDC`
- `targetGCDC`
- `RenderObjectToDCText`
- `RenderRegionViewOnDCTextOnly`
- `DCRenderText`

这些名称允许只出现在：

- `docs/must_drop.md`
- 审计文档
- 针对禁用词的测试脚本

它们不得重新进入 project-owned 头文件、源文件或可编译接口。

---

## 与上游分类的关系

- `docs/must_drop.md` 已经把 `wxGCDC` 宿主路径标成必须丢弃
- `039-remove-wxgcdc-paths` 在当前仓库状态下的完成标准，是：
  - project-owned 源码里零 `wxGCDC` 路径
  - 有专项 smoke 阻止这些入口回流

---

## 对后续任务的约束

- `040` 不得通过 `wxGLContext` 重新引入旧文本或 GL 目标入口
- `041` 不得通过旧 canvas 包装恢复任何依赖 `wxGCDC` 的宿主绘制语义
