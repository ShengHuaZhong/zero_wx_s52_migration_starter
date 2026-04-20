# rewrite_required.md

## 目标

本文件列出当前候选集合中，**仍然有迁移价值，但不能直接提取或直接 vendoring**
的部分。

判断标准：

- 业务职责在最终架构里仍然需要保留
- 但实现已经和 wx 资源、旧 host API、历史数据结构混在一起
- 因而更适合“按职责重写”为项目自有实现，而不是原样迁移

---

## 1. 文件级重写重点

- `libs/s52plib/src/s52plib.cpp`
- `libs/s52plib/src/s52plib.h`
- `libs/s52plib/src/DepthFont.cpp`
- `libs/s52plib/src/DepthFont.h`
- `libs/s52plib/src/TexFont.cpp`
- `libs/s52plib/src/TexFont.h`
- `gui/include/gui/S57ObjectDesc.h`
- `gui/src/s57obj.cpp`
- `libs/s57-charts/src/ogrs57datasource.cpp`

---

## 2. 重写原因

### `s52plib.cpp` / `s52plib.h`

- 同时混合了：
  - 规则执行
  - 图像 / bitmap 资源
  - DC 路径
  - GL 路径
  - 字体 / 配置入口
- 文件内存在真实迁移价值，但必须拆成更小的 project-owned core / IR /
  renderer-facing 结构

### `DepthFont.*` / `TexFont.*`

- 文字能力未来仍需要，但当前实现直接建立在 `wxFont`、`wxBitmap`、
  `wxMemoryDC` 之上
- 更合理的迁移方式是：
  - 抽出中性 font descriptor
  - 重建 glyph/atlas 生成路径
  - 让最终 renderer 消费 project-owned text IR

### `S57ObjectDesc.h` / `s57obj.cpp`

- 这些位置承载了对象属性文本化、对象描述生成等业务含义
- 但当前接口和 `wxString` / 旧 chart object 语义强耦合
- 更适合在后续 feature / attribute adapter 中重写为项目自有模型

### `ogrs57datasource.cpp`

- 数据源适配职责在最终架构里仍然需要
- 但它属于 chart data ingest / runtime 适配层，不应直接作为
  `s52_core_headless` 代码搬运
- 更适合作为 `chart_runtime` 或输入适配层的重写参考

---

## 3. 与其他分类的边界

- 本清单不是 “must drop” 清单：
  - 它列出的内容仍有业务价值
- 本清单也不是 “headless candidate” 清单：
  - 这些内容往往不能直接进入最终 core，而要先重构/重写

因此：

- `025` 解决“哪些逻辑值得进入 headless core”
- `026` 解决“哪些内容必须重写后才能进入新架构”
- `027` 解决“哪些 wx host 路径应整体丢弃”
