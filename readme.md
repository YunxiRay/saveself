# gitNote
一个基于 git 进行数据同步的云笔记
## 依赖
Qt 5.12.11
## 构建
### 使用 Visual Studio
1. 安装Qt， Visual Studio (MSVC)，Qt VS Tools
1. 打开 gitnote.sln
1. 在 VS 里选择平台和类型进行生成

### 使用 Qt Creator
**不建议，因为现在的 .pro 文件只在子项目中，目前还没有为整个解决方案建立项目文件**     
1. 打开各项目里的 pro 文件
1. 然后直接根据平台和类型生成

## 注意
因为平常使用 VS 开发，且在其中的改动不会同步到 pro 文件上，因此如需使用 Qt Creator 请检查 pro 文件是否正确。
