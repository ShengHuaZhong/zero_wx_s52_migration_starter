# plan.md

## 项目目标

本项目的最终目标是：

**完成 `s52plib` 到零 wx 依赖 headless S-52 portrayal core 的迁移，**
并通过 Qt6 / QRhi 完成最终显示。

项目不迁移 OpenCPN 的应用层、wx UI 层、canvas 层或旧的 wx/OpenGL 渲染宿主。

---

## 最终完成标准

迁移完成必须同时满足：

1. `chartsymbols.xml`、`s57attributes.csv`、`s57objectclasses.csv` 可成功加载。
2. 能完成 `S57 feature -> S52 lookup/CSP -> portrayal IR`。
3. Qt6 / QRhi 成为唯一显示路径。
4. 公共 ABI 零 wx 类型。
5. CMake 零 wxWidgets 依赖。
6. 最终二进制零 wx 链接。
7. 真实 S57 可打开并非空白显示。
8. 至少一组回归场景通过。

---

## 阶段划分

### 阶段 A：仓库骨架与规则固化
目标：
- 固化架构规则
- 固化零 wx 原则
- 建立任务与状态体系

### 阶段 B：上游来源与资产落库
目标：
- 引入并记录上游来源
- 落库 `s57data` 资产
- 建立资产路径和验证规则

### 阶段 C：wx 依赖审计与切边
目标：
- 审计所有 wx 依赖
- 区分可替换类型、资源层依赖、必须删除的 UI/宿主依赖

### 阶段 D：headless S-52 core 提取
目标：
- 建立无 wx 的核心类型
- 加载 symbol / line / pattern / lookup / palette
- 去除 wx 配置、位图、绘图上下文依赖

### 阶段 E：规则执行与 portrayal IR
目标：
- lookup 加载
- CSP 入口桥接
- feature 到 portrayal IR 的转换

### 阶段 F：Qt6 / QRhi 接入
目标：
- point / line / area / text 渲染
- host 非空白显示
- draw priority 和 palette 生效

### 阶段 G：回归与完成迁移
目标：
- 真实 S57 smoke
- golden/regression
- 零 wx 校验
- 完成验收

---

## 本项目明确不做

- 不迁移 wx UI
- 不保留 `wxDC` 绘制路径
- 不保留 `wxGLContext` 作为宿主
- 不把旧 canvas 路径塞进 Qt
- 不让 host 代码承担 portrayal 决策

---

## 执行顺序

必须按顺序推进：

1. 仓库规则
2. 来源与资产
3. wx 审计
4. headless core
5. portrayal IR
6. QRhi 渲染
7. regression 与零 wx 验证
