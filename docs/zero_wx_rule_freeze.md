# zero_wx_rule_freeze.md

## 目标

把“零 wx”从一般性原则冻结成后续任务必须持续满足的硬规则。

这份文档约束 project-owned 代码与构建入口；`third_party/` 和 `vendor/`
中的上游材料仍可保留原始引用，但不得泄漏到公共边界或最终二进制。

---

## 1. 冻结后的硬规则

### 项目自有源码零 wx include

- `include/` 与 `src/` 中不得出现任何 `wx/*.h`

### 项目自有源码零 wx 类型

以下类型不得出现在 project-owned 源码或公共头中：

- `wxString`
- `wxColour`
- `wxColor`
- `wxPoint`
- `wxPoint2DDouble`
- `wxRect`
- `wxSize`
- `wxBitmap`
- `wxImage`
- `wxFont`
- `wxFileConfig`
- `wxDC`
- `wxGCDC`
- `wxGLContext`
- `wxWindow`
- `glChartCanvas`

### 项目构建入口零 wxWidgets 依赖

- 不允许 `find_package(wxWidgets)`
- 不允许新增任何 wxWidgets 链接或查找逻辑

### 分层规则保持不变

- `s52_core_headless` 负责规则、lookup、CSP、selection 和 project-owned IR
- `chart_runtime` 负责 runtime orchestration，并且只能消费 project-owned IR
- `chart_qt_host` 只负责 Qt6 / QRhi host 与 present，不拥有 portrayal 规则

---

## 2. 允许的替代方向

- `std::string` 替代 `wxString`
- project-owned `Color`、`Point`、`Rect`、`Size` 等中性值类型替代 wx 值类型
- project-owned image metadata / font descriptor / config loader 替代
  `wxBitmap`、`wxImage`、`wxFont`、`wxFileConfig`
- Qt6 / QRhi 作为唯一显示路径，替代旧 `wxDC` / `wxGCDC` / `wxGLContext`
  / `glChartCanvas` host 路径

---

## 3. 对边界设计的补充冻结

- `s52_core_headless` 可以读取 `chartsymbols.xml`、CSV 和 lookup 资产
- `chart_runtime` 不能自行重新实现 lookup / CSP / symbol 选择
- `chart_qt_host` 不能读取 `chartsymbols.xml`，不能把旧 wx host 路径包装后继续
  使用
- renderer 只消费 project-owned IR

---

## 4. 例外范围

- `third_party/` 与 `vendor/` 中允许保留上游原始 wx 引用，前提是：
  - 保持隔离
  - 不作为 project-owned public API 暴露
  - 不成为最终链接依赖
- 审计与设计文档可以记录 wx 术语，但这不构成对 project-owned 源码的例外

---

## 5. 执行与验证

- 从本任务开始，仓库 smoke 会检查：
  - `docs/zero_wx_rule_freeze.md` 是否仍保留完整禁令
  - `include/` 与 `src/` 是否出现冻结名单中的 wx include / 类型 / host 路径
  - 根 `CMakeLists.txt` 是否出现 `find_package(wxWidgets)` 或 `wxWidgets`
- 更完整的源码/构建级零 wx 校验在 `093` 与 `094` 完成

---

## 6. 变更控制

- 后续任务不得放松这里的规则
- 如果确实需要调整，必须有单独 task 明确修改规则，并同步更新验证
- 在该类 task 出现前，这份 freeze 文档优先于“临时方便”的实现选择
