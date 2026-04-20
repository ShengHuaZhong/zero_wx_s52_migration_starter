# build_environment.md

## 目标

本文件定义本项目的标准构建环境、推荐工具链、本地验证方式，以及云端 Codex 与本地 Windows 编译之间的边界。

本项目的**最终构建与 GUI 验证以本地 Windows 环境为准**。  
云端 Codex 可以读取、修改和提交代码，但不作为最终 Qt GUI 行为的验收环境。

---

## 1. 标准本地环境

### 操作系统
- Windows 11 x64
- Windows 10 x64 也可接受，但以 Windows 11 为优先验证环境

### 编译器
- Visual Studio 2022
- MSVC v143 toolset
- 建议安装：
  - Desktop development with C++
  - CMake tools for Windows
  - Windows 10/11 SDK

### 关键工具版本
- CMake: 3.29+
- Ninja: 1.11+（可选，但推荐）
- Git: 2.40+
- Python: 3.11+
- 7-Zip 或 tar/unzip：用于资产与测试数据处理

### Qt
- Qt 6.8+，推荐 Qt 6.9.x 或更高的小版本
- 必须包含：
  - Qt Base
  - Qt Gui
  - Qt Widgets
- 如项目进入 QRhi 阶段，还需要：
  - Qt Shader Tools（若后续 shader 编译流程使用）
  - 与 Qt 版本匹配的 MSVC kit

### 包管理
- vcpkg（推荐）
- 也允许纯系统依赖 + 手工指定 Qt/CMake 路径，但必须在 `CMakePresets.json` 中可复现

---

## 2. 本项目的环境边界

### 云端 Codex 负责
- 读取 GitHub 仓库
- 修改代码
- 生成分支或 PR
- 做纯源码级和无 GUI 依赖的检查
- 更新任务与状态文件

### 本地机器负责
- 真正的 Windows + MSVC + Qt 编译
- Qt Widgets / QRhi 行为验证
- 真实图形显示验证
- 最终 smoke 和回归确认

### 不允许混淆
- 不要把云端通过当成本地 GUI 已通过
- 不要把本地临时环境配置写死到源码中
- 不要依赖 IDE 私有设置作为唯一构建方式

---

## 3. 目录与环境变量约定

### 推荐目录
- 仓库根目录：任意，但避免中文路径和过长路径
- Qt 安装目录：例如 `C:/Qt/6.9.1/msvc2022_64`
- vcpkg 目录：例如 `C:/dev/vcpkg`
- 测试数据目录：例如 `C:/chart_testdata`

### 推荐环境变量
可选，但推荐统一：
- `QT_ROOT`
- `VCPKG_ROOT`
- `S57_TESTDATA_ROOT`
- `S52_ASSET_ROOT`

### 规则
- 不依赖开发者个人用户名路径
- 不把本机绝对路径硬编码进源码
- 允许在 `CMakePresets.json`、`docs/local_compile.md`、脚本里引用环境变量
- 缺失环境变量时，必须报清晰错误或给出 fallback 说明

---

## 4. CMake 约束

### 必须提供
- configure preset
- build preset
- test preset

### 推荐命名
- `windows-msvc-debug`
- `windows-msvc-release`
- `build-windows-msvc-debug`
- `build-windows-msvc-release`
- `test-windows-msvc-debug`
- `test-windows-msvc-release`

### 规则
- 所有本地验证命令必须可以从仓库根目录直接执行
- 不依赖手工点 IDE 按钮完成唯一构建
- 新增模块后必须同步更新 CMake target 与 install/export 规则（如适用）
- 不允许重新引入 `find_package(wxWidgets)`

---

## 5. 构建类型

### Debug
用于：
- 开发
- 单元测试
- 日志检查
- 运行 smoke

### Release
用于：
- 性能初检
- 更接近真实部署的打包与运行行为

### 规则
- 新任务默认先保证 Debug 可构建
- 涉及渲染和行为稳定后，再扩到 Release
- 不要为追求 Release 通过而牺牲 Debug 可读性

---

## 6. 推荐本地构建命令

### configure
```powershell
cmake --preset windows-msvc-debug
```

### build
```powershell
cmake --build --preset build-windows-msvc-debug
```

### test
```powershell
ctest --preset test-windows-msvc-debug --output-on-failure
```

### release configure/build
```powershell
cmake --preset windows-msvc-release
cmake --build --preset build-windows-msvc-release
ctest --preset test-windows-msvc-release --output-on-failure
```

---

## 7. 本地 GUI / host 验证

对于带 Qt host 的阶段，至少要做：

1. 能启动 standalone 或测试 host
2. 能打开最小测试图表或 fixture
3. 画面不是纯空白
4. resize 后没有明显退化
5. 不依赖 wx 动态库

### 示例命令
```powershell
./out/build/windows-msvc-debug/apps/chart_standalone/chart_standalone.exe --smoke-test
```

如果某阶段还没有 standalone，可接受以专门的 smoke test target 替代。

---

## 8. 测试数据策略

### 测试数据分层
- 公开可提交的小型 fixture：放仓库内
- 体积大、受许可或私有测试数据：放仓库外，通过环境变量指向

### 规则
- 代码必须允许“无真实 ENC 数据”时运行最小单元测试
- 有真实数据时，额外启用 host smoke / regression
- 缺数据时应 Skip 或清晰 Fail，不能静默通过

---

## 9. 日志与失败策略

### 规则
- 资产缺失、路径错误、配置错误必须输出清晰日志
- 构建脚本失败时要保留足够上下文
- smoke 失败时要能区分：
  - 编译失败
  - 资源缺失
  - 运行时空白渲染
  - 回归不一致

---

## 10. 云端 Codex 使用约束

### 允许
- 更新源码
- 更新文档
- 更新 tasks 与 state
- 运行轻量测试
- 准备 PR

### 不允许假定
- 云端容器等同于本地 Windows + Qt GUI 环境
- 云端已验证真实 host 显示
- 云端拥有本地未 push 的代码或私有测试数据

### 推荐工作流
1. 云端 Codex 改代码
2. 生成分支/PR
3. 本地拉取
4. 本地 Windows 编译
5. 本地 GUI/smoke 验证
6. 再决定 merge

---

## 11. 迁移完成前的硬性检查

本项目进入“完成迁移”验收前，必须同时满足：

- Debug 构建通过
- 关键测试通过
- host smoke 通过
- 最终二进制零 wx 链接
- 公共头零 wx 类型
- 本地 Windows 环境可复现构建
