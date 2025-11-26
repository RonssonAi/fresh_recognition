# Model Import | 模型导入

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
int SmartPredictor_import_model(const char* model_directory, const char* rrm_path);
```

## Purpose | 用途

Import the model data from the specified path.
从指定路径导入模型数据。

## Parameters | 参数

- `model_directory`: Model directory
  - `model_directory`: 模型目录
  - Type: `const char*`
  - 类型: `const char*`
  - Description: Directory to import the model
  - 描述: 导入模型放置目录
  - Example: `"./model"`
  - 示例: `"./model"`
- `rrm_path`: rrm file path
  - `rrm_path`: rrm文件的路径
  - Type: `const char*`
  - 类型: `const char*`
  - Description: Path of rrm which need import
  - 描述: 导入rrm文件的路径
  - Example: `"./export/model_ncnn.rrm"`
  - 示例: `"./export/model_ncnn.rrm"`

## Returns | 返回值

- `>= 0`: Import successful (returns success code)
- `>= 0`: 导入成功（返回成功代码）
- `< 0`: Import failed
- `< 0`: 导入失败

## Example | 示例

```cpp
// Import the model
// 导入模型
int result = SmartPredictor_import_model("./model", "./export/model_ncnn.rrm");
if (result < 0) {
    std::cerr << "Failed to import model with error code: " << result << std::endl;
    return;
} else {
    std::cout << "Model import successfully" << std::endl;
}
```

## Notes | 注意事项

- The rrm file must be existed
- rrm文件必须存在

## Related Documentation | 相关文档

- [Main Documentation | 主文档](../README.md) - Back to main documentation | 返回主文档
- [SDK Authorization | SDK授权](authorization.md) - Required before loading models | 加载模型前必需
- [Image Prediction | 图像预测](prediction.md) - Use loaded models for classification | 使用加载的模型进行分类
- [Image Registration | 图像注册](registration.md) - Add training data to loaded models | 向加载的模型添加训练数据
- [Model Management | 模型管理](model_management.md) - Save and manage loaded models | 保存和管理加载的模型
- [Model Export | 模型导出](model_export.md) - Export the model | 导出模型数据
