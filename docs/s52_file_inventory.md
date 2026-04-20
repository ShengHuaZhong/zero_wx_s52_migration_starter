# s52_file_inventory.md

## 目标

本文件清点 OpenCPN `Release_5.12.4` / commit
`37fd0cddb7334fe489e9f18aa163977a9c5c84f7` 中，准备进入零 wx 迁移审计范围的
S-52 相关源码与资产集合。

它是后续 `021` 到 `029` 审计/分类任务的共同输入，不代表这些文件都会被原样导入。

---

## 1. 已导入的 `s57data` 资产

当前已在 `vendor/opencpn_s57data/` 落库：

- `chartsymbols.xml`
- `s57attributes.csv`
- `s57objectclasses.csv`
- `rastersymbols-day.png`
- `rastersymbols-dusk.png`
- `rastersymbols-dark.png`

这些文件构成后续 headless asset loader 的最小输入集合。

---

## 2. 上游 `data/s57data/` 中尚未导入的文件

仍在上游 snapshot 中、但当前未导入本仓库的文件：

- `data/s57data/attdecode.csv`
- `data/s57data/Helvetica.txf`
- `data/s57data/S52RAZDS.RLE`
- `data/s57data/s57expectedinput.csv`

说明：

- 这些文件是否需要进入最终迁移路径，还要经过后续 wx 审计、headless 候选分类和
  loader 设计判断
- `S52RAZDS.RLE` 属于需要特别审查的遗留产物，不在当前资产导入任务中自动带入

---

## 3. 主要 S-52 核心源码候选

以下是当前上游 snapshot 中最直接的 `s52plib` 代码集合：

- `libs/s52plib/CMakeLists.txt`
- `libs/s52plib/src/Cs52_shaders.cpp`
- `libs/s52plib/src/Cs52_shaders.h`
- `libs/s52plib/src/DepthFont.cpp`
- `libs/s52plib/src/DepthFont.h`
- `libs/s52plib/src/TexFont.cpp`
- `libs/s52plib/src/TexFont.h`
- `libs/s52plib/src/chartsymbols.cpp`
- `libs/s52plib/src/chartsymbols.h`
- `libs/s52plib/src/color_types.h`
- `libs/s52plib/src/mygeom.cpp`
- `libs/s52plib/src/mygeom.h`
- `libs/s52plib/src/s52cnsy.cpp`
- `libs/s52plib/src/s52plib.cpp`
- `libs/s52plib/src/s52plib.h`
- `libs/s52plib/src/s52plibGL.h`
- `libs/s52plib/src/s52s57.h`
- `libs/s52plib/src/s52shaders.cpp`
- `libs/s52plib/src/s52shaders.h`
- `libs/s52plib/src/s52utils.cpp`
- `libs/s52plib/src/s52utils.h`

这些文件将在后续任务中继续区分为：

- 可 headless 提取
- 需要中性类型改写
- 必须删除的 GL / host / wx 路径

---

## 4. 邻近的 chart 集成文件

以下文件不属于 `libs/s52plib` 本体，但和 S-52 数据流强相关，需要进入后续审计：

- `gui/include/gui/S57ObjectDesc.h`
- `gui/include/gui/chartimg.h`
- `gui/include/gui/s57chart.h`
- `gui/src/chartimg.cpp`
- `gui/src/s57chart.cpp`
- `gui/src/s57obj.cpp`
- `libs/s57-charts/src/ogrs57datasource.cpp`

这些文件后续主要用于判断：

- 哪些是 feature / attribute 适配输入
- 哪些仍然带着 wx / host / old canvas 耦合
- 哪些不应进入最终 headless core

---

## 5. 本清单的用途边界

本清单只负责“列出候选集合”，不负责：

- 许可证判定
- provenance pin
- wx 依赖分类结论
- 是否最终保留某个文件
- 真正的代码导入
