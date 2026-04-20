# asset_path_policy.md

## 目标

本文件定义 `s57data` 资产在本项目中的路径规则、查找顺序和分层责任。

目标是让后续 loader 可以在**零 wx 依赖**前提下稳定找到：

- `chartsymbols.xml`
- `s57attributes.csv`
- `s57objectclasses.csv`
- `rastersymbols-day.png`
- `rastersymbols-dusk.png`
- `rastersymbols-dark.png`

同时保持 line/pattern 这类嵌入式资产的路径边界清晰。

---

## 1. 规范资产根目录

本项目当前的规范资产根目录定义为：

- `vendor/opencpn_s57data/`

“资产根目录”是指**直接包含**以下文件的目录：

- `chartsymbols.xml`
- `s57attributes.csv`
- `s57objectclasses.csv`
- `rastersymbols-*.png`

因此：

- loader 接收的是目录路径，不是单个 XML 文件路径
- `chartsymbols.xml` 中引用的相对图形文件名，默认都相对这个目录解析

---

## 2. 路径解析顺序

后续 loader / init 代码必须使用以下顺序解析资产根目录：

1. 调用方显式传入的资产根目录
2. 环境变量 `S52_ASSET_ROOT`
3. 开发期仓库内 fallback：`<repo>/vendor/opencpn_s57data`

规则：

- 一旦命中有效目录，不再继续猜测其他路径
- 不允许使用 wx 配置、注册表、用户 profile 文件等宿主特定路径机制
- 缺失时必须输出清晰错误，指出缺失的是“资产根目录”还是具体文件

---

## 3. 文件解析规则

### 直接按文件名定位的资产

以下文件直接位于资产根目录：

- `chartsymbols.xml`
- `s57attributes.csv`
- `s57objectclasses.csv`
- `rastersymbols-day.png`
- `rastersymbols-dusk.png`
- `rastersymbols-dark.png`

### 由 XML 间接引用的图形文件

`chartsymbols.xml` 中当前引用的是：

- `rastersymbols-day.png`
- `rastersymbols-dusk.png`
- `rastersymbols-dark.png`

这些文件必须按**相对于资产根目录**的规则解析，不得写死用户机器绝对路径。

### 嵌入式资产

以下资产不需要单独路径解析：

- line styles：嵌入 `chartsymbols.xml` 的 `<line-styles>` 段
- area patterns：嵌入 `chartsymbols.xml` 的 `<patterns>` 段

---

## 4. 分层责任

### `s52_core_headless`

- 负责最终资产路径解析
- 负责加载 XML / CSV / raster symbol atlas
- 负责报告缺失或格式错误

### `chart_runtime`

- 可以把资产根目录作为初始化输入传给 core
- 不负责重新定义文件名规则

### `chart_qt_host` / standalone host

- 不得拥有独立的资产查找策略
- 不得读取 `chartsymbols.xml` 决定 portrayal 规则
- 只允许把显式配置传给 runtime/core

---

## 5. 失败策略

如果路径解析失败，后续实现必须：

- 明确报出尝试过的资产根目录
- 明确报出缺失的文件名
- 不静默降级到未审计的替代资产
- 不因为 host 层差异而分叉规则

---

## 6. 本任务不做什么

本任务只固化路径规则，不实现：

- 真正的 XML / CSV / PNG loader
- host 参数解析
- 环境变量绑定代码
- 任何 wx 配置兼容层
