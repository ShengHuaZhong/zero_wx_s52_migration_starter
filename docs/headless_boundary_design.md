# headless_boundary_design.md

## 目标

在进入 `s52_core_headless` 模块创建与中性类型替换之前，先冻结
`s52_core_headless`、`chart_runtime`、`chart_qt_host` 之间的职责边界。

这份设计文档只定义边界，不提前实现后续模块代码。

---

## 1. 总体数据流

新的主路径固定为：

`chart data adapter -> chart_runtime feature model -> s52_core_headless -> project-owned InstructionIR -> chart_runtime render orchestration -> chart_qt_host -> Qt6 / QRhi`

关键约束：

- `vendor/opencpn_s57data/` 下的 `chartsymbols.xml`、CSV 和 symbol atlas 只由
  `s52_core_headless` 侧的 loader 读取
- `chart_runtime` 是运行时中心，负责 feature、scene、viewport、调用编排和
  renderer orchestration
- `chart_qt_host` 只负责 widget/window、输入桥接和 present
- renderer 只能消费 project-owned IR，不能消费 wx 类型、Qt Widgets 类型、
  或上游私有结构

---

## 2. `s52_core_headless` 边界

### 拥有职责

- `chartsymbols.xml`、颜色表、symbol / line / pattern 元数据加载
- lookup 原始数据加载与索引构建
- CSP 入口与执行
- object class / attribute 到 lookup key 的映射
- point / line / area / text / display priority 选择
- portrayal `InstructionIR` 生成

### 可作为实现参考的上游来源

这些文件的业务逻辑值得迁入 headless core，但必须按后续任务做 project-owned
改写：

- `libs/s52plib/src/chartsymbols.cpp`
- `libs/s52plib/src/chartsymbols.h`
- `libs/s52plib/src/color_types.h`
- `libs/s52plib/src/mygeom.cpp`
- `libs/s52plib/src/mygeom.h`
- `libs/s52plib/src/s52cnsy.cpp`
- `libs/s52plib/src/s52s57.h`
- `libs/s52plib/src/s52utils.cpp`
- `libs/s52plib/src/s52utils.h`

### 输入

- `chart_runtime` 提供的 project-owned feature / geometry / attribute 视图
- viewport、mariner settings、palette / display mode 之类的中性值类型
- 从 `vendor/` 读取的规则资产与元数据

### 输出

- project-owned `InstructionIR`
- symbol / line / pattern / text 选择结果中的稳定 ID、名称或索引
- 可调试的 rule / lookup / CSP 决策结果

### 不拥有的职责

- OGR/S57 数据源生命周期
- scene graph / render frame 调度
- GPU API、QRhi、QWidget、QWindow
- wxWidgets、windowing、host 输入
- 最终 atlas 上传或 present

### 公共边界要求

- 只暴露窄而稳定的 project-owned API
- 公共头文件不得出现 wx 类型、Qt Widgets 类型或上游私有实现细节
- 允许临时 compatibility shim，但它们只能留在模块私有实现内

---

## 3. `chart_runtime` 边界

### 拥有职责

- chart data adapter 输出的 project-owned feature model
- scene model、viewport、runtime API
- 调用 `s52_core_headless` 的 orchestration
- `InstructionIR` 的收集、排序、帧组织和 renderer 输入准备
- palette/runtime state、draw order、open-chart flow

### 调用方式

`chart_runtime` 负责：

- 持有 chart/session 生命周期
- 把 feature / viewport / mariner settings 传给 `s52_core_headless`
- 接收 `InstructionIR`
- 把 `InstructionIR` 组织成 renderer 可消费的帧数据

### 不拥有的职责

- `chartsymbols.xml` / CSV 的解析
- lookup 规则和 CSP 逻辑
- symbol / line / pattern / text 选择
- Qt widget 生命周期
- 旧 `wxDC` / `wxGCDC` / `wxGLContext` 渲染入口

### 上游参考放置原则

- `libs/s57-charts/src/ogrs57datasource.cpp` 只作为 runtime 输入适配层重写参考
- `gui/include/gui/S57ObjectDesc.h` / `gui/src/s57obj.cpp` 中仍有业务意义的
  属性文本化逻辑，应转成 runtime 的 project-owned feature/attribute adapter

---

## 4. `chart_qt_host` 边界

### 拥有职责

- QWidget / QWindow host
- resize / input / event bridge
- Qt6 / QRhi 设备与 present 相关宿主逻辑

### 不拥有的职责

- `chartsymbols.xml`、颜色表、lookup 数据加载
- CSP 执行
- portrayal rule 选择
- 直接消费上游私有结构
- 旧 `glChartCanvas` 语义的任何延续

### 与 runtime 的关系

- host 只调用 `chart_runtime` 的窄 API
- host 不判断图元用什么 symbol / line / pattern / text
- host 不重新打开旧 wx / GL 绘制路径

---

## 5. 明确排除的路径

以下内容不属于新的 headless core 边界，且不能通过包装重新进入主线：

- `libs/s52plib/src/s52plibGL.h`
- `libs/s52plib/src/Cs52_shaders.cpp`
- `libs/s52plib/src/Cs52_shaders.h`
- `libs/s52plib/src/s52shaders.cpp`
- `libs/s52plib/src/s52shaders.h`
- 任何以 `wxDC`、`wxGCDC`、`wxGLContext` 为中心的旧渲染入口
- 任何 `glChartCanvas::*` 直接调用路径

这些路径的价值属于旧 host 实现方式，而不是最终架构中要保留的 portrayal
决策逻辑。

---

## 6. 需要重写但不进入 host 的部分

以下内容仍有迁移价值，但不能按旧边界直接搬入 core 或 host：

### `s52plib.cpp` / `s52plib.h`

- 不能保留 monolith 入口
- 需要拆成 headless loader / lookup / CSP / selection / IR 相关的 project-owned
  子职责
- 原来的 DC / GL / text target 入口按 `must_drop` 清单删除

### `DepthFont.*` / `TexFont.*`

- 文字能力要保留，但旧实现基于 `wxFont` / `wxBitmap` / `wxMemoryDC`
- 正确去向是：
  - 规则侧：保留 text rule 选择与 text IR
  - 渲染侧：后续以 project-owned font descriptor 和 renderer 路径重建

### `S57ObjectDesc.h` / `s57obj.cpp`

- 保留对象属性表达的业务含义
- 不保留 `wxString` 和旧 chart object 接口
- 后续放入 runtime 侧的 feature / attribute adapter

---

## 7. 对后续任务的冻结要求

- `029-zero-wx-rule-freeze` 必须把这里的边界继续固化为明确规则
- `030-create-s52-core-headless-module` 只能按这里定义的 ownership 建模块
- `031` 到 `041` 只能做中性类型替换和旧 host 路径删除，不能把规则职责推给
  Qt host
- `042` 到 `070` 在 `s52_core_headless` 内补齐 loader、lookup、CSP、selection
  和 IR
- `071` 之后的 runtime / renderer / host 任务只能消费 project-owned IR，
  不能回流到 wx 路径

---

## 8. 本任务不改变什么

- 不创建 `s52_core_headless` 的真实实现文件
- 不定义最终 public API 细节
- 不开始 neutral type 替换
- 不提前删除旧 upstream 文件
- 不引入 Qt、wx 或 GPU 代码
