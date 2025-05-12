# Fresh Recognition

基于深度学习的图像识别系统，支持图像注册和预测功能。

## 快速导航

- [项目文档](docs/index.md)
- [API文档](docs/api/overview.md)
- [使用示例](docs/examples/basic.md)
- [常见问题](docs/faq.md)

## 主要特性

- 🚀 简单易用的 API 接口
- 📸 支持图像注册和预测
- 🎯 高精度的识别结果
- 🔄 支持模型在线更新
- 📊 可配置的相似度阈值
- 💾 模型持久化存储

## 快速开始

```cpp
// 1. 加载模型
std::string model_dir = "path/to/model";
int result = SmartPredictor_load(model_dir);

// 2. 注册图像
std::string label = "apple";
result = SmartPredictor_regist_img(img_bytes, img_size, label);

// 3. 预测图像
std::string prediction = SmartPredictor_predict_img_filter(img_bytes, img_size, 0.6);
```

## 系统要求

- C++11 或更高版本
- OpenCV 4.x
- CMake 3.10 或更高版本

## 安装说明

详细的安装说明请参考[安装文档](docs/getting-started/installation.md)。

## 文档

完整的文档请访问 [docs](docs/) 目录：

- [快速开始](docs/getting-started/quickstart.md)
- [API文档](docs/api/overview.md)
- [示例代码](docs/examples/basic.md)
- [常见问题](docs/faq.md)

## 支持与反馈

如果您在使用过程中遇到任何问题，或有任何建议，请通过以下方式联系我们：

- 提交 Issue
- 联系技术支持团队

## 许可证

本项目采用 [MIT 许可证](LICENSE)。 