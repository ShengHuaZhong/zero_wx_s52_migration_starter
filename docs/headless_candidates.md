# headless_candidates.md

## 目标

本文件列出在当前上游快照中，**最有可能进入 `s52_core_headless`** 的候选文件。

判断标准：

- 职责明显属于 S-52 规则、资产、几何或 CSP
- 不以 wx host / canvas / GL context 作为核心职责
- 即使仍需中性类型改写，也值得保留其业务逻辑

本清单是“候选集合”，不是“可直接复制集合”。

---

## 1. 直接 headless 候选

- `libs/s52plib/src/chartsymbols.cpp`
- `libs/s52plib/src/chartsymbols.h`
- `libs/s52plib/src/color_types.h`
- `libs/s52plib/src/mygeom.cpp`
- `libs/s52plib/src/mygeom.h`
- `libs/s52plib/src/s52cnsy.cpp`
- `libs/s52plib/src/s52s57.h`
- `libs/s52plib/src/s52utils.cpp`
- `libs/s52plib/src/s52utils.h`

---

## 2. 候选理由

### `chartsymbols.*`

- 负责 `chartsymbols.xml`、颜色表、symbol / line / pattern 元数据解析
- 业务职责明显属于 headless 资产加载层
- 虽然当前仍依赖 `wxString` / `wxImage` / `wxBitmap`，但这些更像可替换实现细节

### `color_types.h`

- 主要是颜色表与相关数据结构
- 适合后续替换成项目自有颜色类型与容器

### `mygeom.*`

- 主要是几何数据与几何算法
- 当前 `wxPoint2DDouble` 依赖是中性几何类型替换问题，而不是 host 路径问题

### `s52cnsy.cpp`

- 明显属于 CSP / 条件符号逻辑
- 虽然 `wxString` 命中极高，但业务职责仍是 headless core 应保留的规则逻辑

### `s52s57.h`

- 处于 S-52 / S-57 规则数据接口边界
- 更像规则层数据结构，而不是宿主层入口

### `s52utils.*`

- 当前没有重度轻量值类型或资源层命中
- 适合作为后续辅助逻辑候选继续审查

---

## 3. 暂不放入 headless 候选的文件

以下文件当前**不**放进本任务的 headless 候选清单：

- `libs/s52plib/src/s52plib.cpp`
- `libs/s52plib/src/s52plib.h`
- `libs/s52plib/src/s52plibGL.h`
- `libs/s52plib/src/Cs52_shaders.*`
- `libs/s52plib/src/s52shaders.*`
- `libs/s52plib/src/DepthFont.*`
- `libs/s52plib/src/TexFont.*`
- `gui/include/gui/*`
- `gui/src/*`
- `libs/s57-charts/src/ogrs57datasource.cpp`

原因：

- 这些文件要么直接暴露 host / DC / GL 入口
- 要么承担字体、shader、canvas、chart host 等非 headless 核心职责
- 要么仍需先经由 `026` / `027` 做更严格分类

---

## 4. 对后续任务的意义

- `026` 将继续从其余文件中筛出“必须重写”而不是简单提取的部分
- `027` 将继续明确哪些 wx host 路径必须整体丢弃
- `028` 的 headless boundary design 将以本清单作为核心输入之一
