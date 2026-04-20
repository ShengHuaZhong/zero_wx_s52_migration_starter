# architecture.md

## 顶层架构

- `s52_core_headless/`
  - 负责 S-52 资产、lookup、CSP、symbol selection、portrayal IR
  - 零 wx，零窗口依赖，零 GPU API 依赖

- `chart_runtime/`
  - 负责 feature model、scene、viewport、runtime API、render orchestration
  - 只消费项目自有 portrayal IR

- `chart_qt_host/`
  - 负责 Qt host、事件桥接、窗口显示
  - 不承担 portrayal 决策

## 关键边界

1. 上游规则与资产 ≠ 最终渲染器。
2. 渲染器只认项目自有 IR。
3. Host 只认 runtime，不认 S-52 规则细节。
4. 零 wx 是硬边界，不是后期优化项。
