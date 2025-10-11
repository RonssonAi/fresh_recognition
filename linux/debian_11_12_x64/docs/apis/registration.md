# Image Registration | 图像注册

## Table of Contents | 目录

- [Function | 函数](#function)
- [Purpose | 用途](#purpose)
- [Parameters | 参数](#parameters)
- [Returns | 返回值](#returns)
- [Example | 示例](#example)
- [Related Documentation | 相关文档](#related-documentation)

## Function | 函数

```cpp
int SmartPredictor_regist_img(unsigned char* imageData, long byteSize, std::string label, int pos);
```

## Purpose | 用途

Registers a new image and its label to the model. This function is used to add new training data to improve the model's recognition capabilities.
向模型注册新图像及其标签。此函数用于添加新的训练数据以提高模型的识别能力。

## Parameters | 参数

- `imageData`: Image data byte array | 图像数据字节数组

  - Type: `unsigned char*` | 类型: `unsigned char*`
  - Description: Raw image data in bytes | 描述: 原始图像数据（字节格式）
  - Format: JPEG, PNG, or BMP | 格式: JPEG、PNG或BMP
- `byteSize`: Size of image data | 图像数据大小

  - Type: `long` | 类型: `long`
  - Description: Size of the image data in bytes | 描述: 图像数据的字节大小
  - Note: Must be accurate to prevent buffer overflows | 注意: 必须准确以防止缓冲区溢出
- `label`: Image label | 图像标签

  - Type: `std::string` | 类型: `std::string`
  - Description: Category or class name for the image | 描述: 图像的类别或类名
  - Example: `"apple"`, `"banana"` | 示例: `"apple"`, `"banana"`
- `pos`: position/index | 位置/索引

  - Type: `int` | 类型: `int`
  - Description: The ranking of the item for prediction. value from 1 to 6. After each predict, the user interface selects the result and records the index. You can then call regist with the index passed in from 1-6. If the user did not select a result for predict, pass in 6. This parameter is used to optimize the effect of the algorithm. | 描述: 预测项目的排名，值从1到6。每次预测后，用户界面选择结果并记录索引。然后您可以使用从1-6传入的索引调用注册。如果用户没有为预测选择结果，则传入6。此参数用于优化算法的效果。
  - Value: `optional range [1-6]` | 值: `可选范围[1-6]`

## Returns | 返回值

- `>= 0`: Registration successful (returns the number of inserted features) | 注册成功（返回插入的特征数量）
- `< 0`: Registration failed | 注册失败

## Example | 示例

```cpp
// Read image file | 读取图像文件
std::vector<unsigned char> imageData = readImage("apple.jpg");

// Register the image | 注册图像
int result = SmartPredictor_regist_img(
    imageData.data(),
    imageData.size(),
    "apple",
    6
);

if (result < 0) {
    std::cerr << "Registration failed with code: " << result << std::endl;
    return;
}
```

## Related Documentation | 相关文档

- [Main Documentation | 主文档](../README.md) - Back to main documentation | 返回主文档
- [SDK Authorization | SDK授权](authorization.md) - Required before using registration | 使用注册功能前必需
- [Model Loading | 模型加载](model_load.md) - Load models before registration | 注册前加载模型
- [Image Prediction | 图像预测](prediction.md) - Use prediction results to guide registration | 使用预测结果指导注册
- [Model Management | 模型管理](model_management.md) - Save registered data and manage models | 保存注册数据和管理模型
