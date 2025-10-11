# Model Management | 模型管理

## Table of Contents | 目录

- [Save Model | 保存模型](#save-model)
- [Reset Model | 重置模型](#reset-model)
- [Delete Label | 删除标签](#delete-label)
- [Unload Model | 卸载模型](#unload-model)
- [Examples | 示例](#examples)
- [Related Documentation | 相关文档](#related-documentation)

This document covers the model management APIs including saving, resetting, and deleting operations.
本文档涵盖了模型管理API，包括保存、重置和删除操作。

## Save Model | 保存模型

### Function | 函数

```cpp
int SmartPredictor_save(const std::string model_dir);
```

### Purpose | 用途

- Saves the model to the disk. It is recommended to save the model when the system is idle or after a certain number of registrations.
- 将模型保存到磁盘。建议在系统空闲时或完成一定数量的注册后保存模型。
- Saving the model to the disk requires a lot of disk I/O. It is recommended to save when the system is idle or after a certain amount of REGIST; for example, calling once after accumulative 30 times of REGIST.
- 将模型保存到磁盘需要大量的磁盘I/O操作。建议在系统空闲时或完成一定数量的注册后保存；例如，在累积30次注册后调用一次。

### Parameters | 参数

- `model_dir`: Model save path | 模型保存路径
  - Type: `std::string` | 类型: `std::string`
  - Description: Path where the model will be saved | 描述: 模型将被保存的路径
  - Example: `"./model"` | 示例: `"./model"`

### Returns | 返回值

- `>= 0`: Save successful | 保存成功
- `< 0`: Save failed | 保存失败

## Reset Model | 重置模型

### Function | 函数

```cpp
bool SmartPredictor_reset(const std::string model_dir);
```

### Purpose | 用途

Clears all data from the model. This operation is irreversible.
清除模型中的所有数据。此操作不可逆。

### Parameters | 参数

- `model_dir`: Model save path | 模型保存路径
  - Type: `std::string` | 类型: `std::string`
  - Description: Path where the model will be saved | 描述: 模型将被保存的路径
  - Example: `"./model"` | 示例: `"./model"`

### Returns | 返回值

- `true`: Reset successful | 重置成功
- `false`: Reset failed | 重置失败

## Delete Label | 删除标签

### Function | 函数

```cpp
bool SmartPredictor_delete(const std::string label);
```

### Purpose | 用途

Deletes all image data associated with the specified label from the model.
从模型中删除与指定标签关联的所有图像数据。

### Parameters | 参数

- `label`: Label name to delete | 要删除的标签名称
  - Type: `std::string` | 类型: `std::string`
  - Description: Name of the category to remove | 描述: 要删除的类别名称
  - Example: `"apple"` | 示例: `"apple"`

### Returns | 返回值

- `true`: Deletion successful | 删除成功
- `false`: Deletion failed | 删除失败

## Unload Model | 卸载模型

### Function | 函数

```cpp
int SmartPredictor_unload();
```

### Purpose | 用途

Releases resources of the loaded model.
释放已加载模型的资源。

### Parameters | 参数

None | 无

### Returns | 返回值

- `0`: Unload successful | 卸载成功
- Other values: Unload failed | 其他值: 卸载失败

## Examples | 示例

### Save Model | 保存模型

```cpp
// Save model after modifications | 修改后保存模型
if (SmartPredictor_save("./model") < 0) {
    std::cerr << "Failed to save model" << std::endl;
    return;
}
```

### Reset Model | 重置模型

```cpp
// Reset model (irreversible) | 重置模型（不可逆）
if (!SmartPredictor_reset("./model")) {
    std::cerr << "Failed to reset model" << std::endl;
    return;
}
```

### Delete Label | 删除标签

```cpp
// Delete a specific label | 删除特定标签
if (!SmartPredictor_delete("apple")) {
    std::cerr << "Failed to delete label" << std::endl;
    return;
}
```

### Unload Model | 卸载模型

```cpp
// Release model resources | 释放模型资源
if (SmartPredictor_unload() != 0) {
    std::cerr << "Failed to release model" << std::endl;
    return;
}
```

## Related Documentation | 相关文档

- [Main Documentation | 主文档](../README.md) - Back to main documentation | 返回主文档
- [SDK Authorization | SDK授权](authorization.md) - Required before using model management | 使用模型管理功能前必需
- [Model Loading | 模型加载](model_load.md) - Load models before management operations | 管理操作前加载模型
- [Image Registration | 图像注册](registration.md) - Register data before saving models | 保存模型前注册数据
- [Image Prediction | 图像预测](prediction.md) - Use models for classification | 使用模型进行分类
