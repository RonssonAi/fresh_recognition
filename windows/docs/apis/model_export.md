# Model Export | 模型导出

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
int SmartPredictor_export_model(const char* model_directory, const char* save_directory, int model_type);
```

## Purpose | 用途

Export the model data to the specified path.
导出模型数据到指定路径。

## Parameters | 参数

- `model_directory`: Model directory
  - `model_directory`: 模型目录
  - Type: `const char*`
  - 类型: `const char*`
  - Description: Directory where model in
  - 描述: 模型所在目录
  - Example: `"./model"`
  - 示例: `"./model"`
- `save_directory`: Model save directory
  - `save_directory`: 模型保存目录
  - Type: `const char*`
  - 类型: `const char*`
  - Description: Directory to save model
  - 描述: 模型保存目录
  - Example: `"./export/"`
  - 示例: `"./export/"`
- `model_type`: Model type
  - `model_type`: 模型类型
  - Type: `int`
  - 类型: `int`
  - Description: Type identifier for the model
  - 描述: 模型的类型标识符
  - Value: `3` (for fresh food classification)
  - 值: `3`（用于生鲜分类）

## Returns | 返回值

- `>= 0`: Export successful (returns success code)
- `>= 0`: 导入成功（返回成功代码）
- `< 0`: Export failed
- `< 0`: 导入失败

## Example | 示例

```cpp
// Export the model
// 导入模型
int result = SmartPredictor_export_model("./model", "./export/", 3);
if (result < 0) {
    std::cerr << "Failed to export model with error code: " << result << std::endl;
    return;
} else {
    std::cout << "Model export successfully" << std::endl;
}
```

## Notes | 注意事项

- The model files must be existed
- 模型文件必须存在

## Related Documentation | 相关文档

- [Main Documentation | 主文档](../README.md) - Back to main documentation | 返回主文档
- [SDK Authorization | SDK授权](authorization.md) - Required before loading models | 加载模型前必需
- [Image Prediction | 图像预测](prediction.md) - Use loaded models for classification | 使用加载的模型进行分类
- [Image Registration | 图像注册](registration.md) - Add training data to loaded models | 向加载的模型添加训练数据
- [Model Management | 模型管理](model_management.md) - Save and manage loaded models | 保存和管理加载的模型
- [Model Import | 模型导入](model_import.md) - Import the model | 导入模型数据
