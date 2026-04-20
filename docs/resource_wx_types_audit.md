# resource_wx_types_audit.md

## 目标

本文件审计候选迁移文件集合中的资源层 wx 类型依赖。

本次聚焦的类型为：

- `wxBitmap`
- `wxImage`
- `wxFont`
- `wxFileConfig`

这些类型对应后续需要替换的：

- 位图 / 图集资源
- 图像解码与像素缓存
- 字体描述与字形缓存
- 配置读取入口

---

## 1. 总量结果

- 有资源层类型命中的文件数：`13`
- 总命中条数：`117`

按类型统计：

- `wxBitmap`: `49`
- `wxImage`: `38`
- `wxFont`: `23`
- `wxFileConfig`: `7`

---

## 2. 命中最重的文件

- `libs/s52plib/src/s52plib.cpp`: `54`
- `gui/src/s57chart.cpp`: `13`
- `gui/src/chartimg.cpp`: `12`
- `libs/s52plib/src/chartsymbols.cpp`: `6`
- `libs/s52plib/src/s52plib.h`: `6`
- `libs/s52plib/src/DepthFont.cpp`: `5`
- `libs/s52plib/src/TexFont.cpp`: `5`

这说明资源层依赖并不只在 GUI 文件里，`s52plib` 本体也深度绑在 wx 图像/字体/配置对象上。

---

## 3. 依赖形态观察

### 图像与位图

- `chartsymbols.cpp` 直接使用 `wxImage` / `wxBitmap` 加载和切片 raster symbol atlas
- `s52plib.cpp` 使用 `wxBitmap` / `wxImage` 参与 symbol、pattern、render buffer 等路径
- `chartimg.cpp` / `s57chart.cpp` 也直接持有缩略图和渲染位图

### 字体

- `DepthFont.cpp` / `TexFont.cpp` 明确基于 `wxFont` 构建纹理字体
- `s52plib.cpp` / `s52plib.h` / `s52s57.h` 也直接传递或存储 `wxFont`

### 配置

- `s52plib.cpp` / `s52plib.h` 使用 `wxFileConfig`
- `chartimg.cpp` 也直接拿到 `wxFileConfig *`

---

## 4. 对后续迁移的含义

- `035-neutral-config-loader` 之前，需要先把 `wxFileConfig` 使用点隔离清楚
- `036-neutral-image-metadata` 和后续 atlas loader 需要承接当前 `wxImage` /
  `wxBitmap` 语义
- `037-neutral-font-descriptor` 需要替代 `wxFont` 的值语义与缓存键
- 这些依赖大多不是“简单替头文件”可以解决的，通常需要 project-owned
  loader / descriptor / cache 重新建模
