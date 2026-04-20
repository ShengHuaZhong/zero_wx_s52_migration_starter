# zero_wx_s52_migration_starter

这是一个“零 wx 依赖的 s52plib 迁移”起步文档包，包含：

- `AGENTS.md`
- `plan.md`
- `docs/`
- `skills/`
- `tasks/001-098.md`
- `state/`
- `scripts/`

用途：
- 作为新项目的起始治理文件
- 供云端 Codex / 本地 Codex CLI 按任务推进
- 供本地 Windows + Qt6 编译与验证

注意：
- 这里不包含 OpenCPN 代码或其资产本体
- 这里只是迁移规划与任务骨架

## Repository skeleton

当前仓库骨架按照零 wx 迁移项目的最小边界预留了以下目录：

- `docs/`：架构、编码规则、构建环境与测试策略文档
- `include/`：稳定公共接口占位
- `src/s52_core_headless/`：headless S-52 portrayal core 占位
- `src/runtime/`：runtime 中心层占位
- `src/qt_host/`：Qt host 层占位
- `skills/`：任务执行技能说明
- `tasks/`：顺序任务定义
- `state/`：当前迭代、已完成项与阻塞项状态
- `test/`：测试与 smoke 占位
- `third_party/`：上游代码与许可证隔离区
- `vendor/`：上游资产落库区


## Added constraints
- `docs/build_environment.md`
- `docs/coding_rules.md`
- aliases: `docs/build_env.md`, `docs/code_rule.md`
