# Model Loading | 模型加载

## Table of Contents | 目录

- [Function | 函数](#function)
- [Purpose | 用途](#purpose)
- [Parameters | 参数](#parameters)
- [Returns | 返回值](#returns)
- [Example | 示例](#example)
- [Notes | 注意事项](#notes)
- [Related Documentation | 相关文档](#related-documentation)

## Function | 函数

```cpp
int SmartPredictor_load(const char* model_directory, int model_type);
```

## Purpose | 用途

Loads the AI model from the specified path. This function must be called after successful authorization and before performing any predictions or registrations.
从指定路径加载AI模型。此函数必须在成功授权后、执行任何预测或注册之前调用。

## Parameters | 参数

- `model_directory`: Model file path

  - `model_directory`: 模型文件路径
  - Type: `const char*`
  - 类型: `const char*`
  - Description: Path to the model directory
  - 描述: 模型目录的路径
  - Example: `"./model"`
  - 示例: `"./model"`
- `model_type`: Model type

  - `model_type`: 模型类型
  - Type: `int`
  - 类型: `int`
  - Description: Type identifier for the model
  - 描述: 模型的类型标识符
  - Value: `4` (for fresh food classification)
  - 值: `4`（用于生鲜分类）

## Returns | 返回值

- `>= 0`: Load successful (returns success code)
- `>= 0`: 加载成功（返回成功代码）
- `< 0`: Load failed
- `< 0`: 加载失败

## Example | 示例

```cpp
// Load the model
// 加载模型
int result = SmartPredictor_load("./model", 4);
if (result < 0) {
    std::cerr << "Failed to load model with error code: " << result << std::endl;
    return;
} else {
    std::cout << "Model loaded successfully" << std::endl;
}
```

## Notes | 注意事项

- The model directory must contain valid model files
- 模型目录必须包含有效的模型文件
- Make sure to call this function after successful SDK authorization
- 确保在SDK授权成功后调用此函数
- The thread number should be optimized based on system resources
- 线程数量应根据系统资源进行优化

## Related Documentation | 相关文档

- [Main Documentation | 主文档](../README.md) - Back to main documentation | 返回主文档
- [SDK Authorization | SDK授权](authorization.md) - Required before loading models | 加载模型前必需
- [Image Prediction | 图像预测](prediction.md) - Use loaded models for classification | 使用加载的模型进行分类
- [Image Registration | 图像注册](registration.md) - Add training data to loaded models | 向加载的模型添加训练数据
- [Model Management | 模型管理](model_management.md) - Save and manage loaded models | 保存和管理加载的模型
