# coding_rules.md

## 目标

本文件定义本项目的编码规则、边界规则和迁移期间的硬约束。  
本项目的首要原则是：

**完成 S-52 portrayal 能力迁移，同时保持零 wx 依赖。**

---

## 1. 总体架构规则

### 核心原则
1. `s52_core_headless` 负责 S-52 规则、lookup、CSP、资产与 portrayal IR 生成
2. `chart_runtime` 是运行时中心
3. Qt host 只是宿主层
4. renderer 只消费项目自有 IR
5. 不把旧宿主架构重新带回项目

### 明确禁止
- 禁止在项目自有代码中包含任何 `wx/*.h`
- 禁止在公共头文件中出现 `wx` 类型
- 禁止在 `chart_qt_host` 或等价宿主层写 lookup/CSP/portrayal 规则
- 禁止让 renderer 直接读取上游原生结构
- 禁止把 `wxDC`、`wxGCDC`、`wxGLContext`、`wxWindow` 之类宿主/绘图类型包装后继续主线使用

---

## 2. 分层边界

### `include/`
- 只能放稳定公共接口
- 不得出现上游私有实现细节
- 不得出现 `wx` 类型
- 不得出现 Qt Widgets 细节，除非该头文件本身属于 Qt host 层公共 API

### `src/s52_core_headless/` 或等价目录
- 可拥有：
  - 资产加载
  - lookup
  - CSP
  - symbol 选择
  - portrayal IR 生成
- 不得依赖：
  - Qt Widgets
  - wxWidgets
  - GPU API
  - host window

### `src/runtime/`
- 拥有 feature model、scene、viewport、runtime API、render orchestration
- 只能接收项目自有 portrayal IR
- 不得把上游原生类型继续向外传递

### `src/qt_host/` / `src/qtwidgets/`
- 只负责 host、事件、窗口和展示
- 不得承担图表规则决定
- 不得读取 `chartsymbols.xml` 或执行 CSP

---

## 3. 零 wx 规则

以下内容是**硬约束**：

- 不 `find_package(wxWidgets)`
- 不链接任何 wx 动态库或静态库
- 不保留 `wxString`、`wxColour`、`wxPoint`、`wxRect`、`wxSize`
- 不保留 `wxBitmap`、`wxImage`、`wxFont`、`wxFileConfig`
- 不保留 `wxDC`、`wxGCDC`、`wxGLContext`、`wxWindow`
- 不保留 `glChartCanvas` 一类旧宿主路径

如果某个任务仍然依赖其中任何一项，该任务**不算完成**。

---

## 4. 上游代码与 vendoring 规则

### 允许
- 在 `third_party/` 中保存上游代码
- 在 `vendor/` 中保存上游资产
- 在项目自有模块中写 compatibility/adapter 层

### 必须做
- 记录来源
- 记录版本、commit/tag
- 记录是否修改
- 记录许可证与分发约束

### 禁止
- 把未经说明的上游代码混入项目自有目录
- 在 vendored 文件上做无记录修改
- 直接把上游内部类型当成本项目稳定 API

---

## 5. 类型与数据结构规则

### 基础类型
- core 层优先使用 STL 与小型 POD/值类型
- 字符串优先 `std::string`
- 使用项目自有 `Color`, `Point`, `Rect`, `Size` 等中性类型
- 容器优先 `std::vector`, `std::unordered_map`, `std::map`, `std::optional`

### 禁止
- 在 core 层使用 QWidget、QObject、QColor、QImage 作为基础业务模型
- 在 core 层重新引入框架锁定的数据结构

### 原则
- 规则层与渲染层之间必须通过 IR 说话
- 数据结构必须便于序列化、日志输出与测试断言

---

## 6. portrayal IR 规则

renderer 只能消费项目自有 IR，例如：

- `PointSymbolIR`
- `LineStyleIR`
- `AreaPatternIR`
- `TextRuleIR`
- `DisplayPriorityIR`
- `InstructionIR`

### 规则
- IR 不得包含 wx 类型
- IR 不得包含 Qt Widgets 类型
- IR 不得直接暴露上游私有结构
- IR 应保持稳定、可调试、可 dump

---

## 7. 命名规则

### 文件名
- 使用小写加连字符或下划线，保持仓库现有风格一致
- task 文件用 `NNN-name.md`
- 避免模糊命名，如 `misc`, `helper`, `temp`, `new`

### 类型名
- 类/结构体：清晰表达职责
- 不允许用 `Manager` 泛滥命名，除非真的负责生命周期/协调
- `Compat`, `Adapter`, `Loader`, `Renderer`, `Bridge`, `Catalog`, `Model`, `IR` 这类后缀要准确使用

### 函数名
- 动词开头
- 表意明确
- 避免缩写过多

---

## 8. 任务执行规则

每次任务只处理**一个边界问题**。

### 每个任务开始前必须写清
- Scope understood
- Layers touched
- What will NOT change

### 每个任务结束后必须更新
- `state/current_iteration.md`
- `state/done.md`
- 或 `state/blocked.md`

### 禁止
- 静默扩大任务范围
- 顺手改 unrelated 文件
- 在没有验证的情况下声称“迁移完成”

---

## 9. 测试与验证规则

### 每次改动至少要有一种验证
- 单元测试
- smoke test
- 规则层 dump 对比
- host 非空白显示验证
- 零 wx 搜索/链接检查

### 规则
- 不能只看计数，不看是否真的显示
- 不能只看云端容器通过，不看本地 Windows 构建
- 不能只看编译通过，不看 runtime 行为

---

## 10. 本地 Windows 构建规则

- 本地 Windows + MSVC + Qt 是最终 GUI 验收环境
- 任何影响 host 显示的任务，都必须在本地环境验证
- 脚本与文档必须可复制执行
- 不依赖 IDE 私有设置作为唯一构建入口

---

## 11. 提交与评审规则

### patch 要求
- 小步
- 可 review
- 可回退
- 有清晰边界

### commit/PR 说明至少应包含
- 改了什么
- 没改什么
- 为什么现在改
- 如何验证
- 还有哪些已知限制

---

## 12. 迁移完成的编码层标准

从编码与构建角度，迁移完成至少意味着：

1. 项目自有源码零 wx include
2. 项目自有源码零 wx 类型
3. 公共头零 wx
4. CMake 零 wxWidgets
5. 最终二进制零 wx 链接
6. portrayal 行为仍可工作
7. Qt6 / QRhi 成为唯一显示路径
