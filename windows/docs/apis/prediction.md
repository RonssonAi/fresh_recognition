# Image Prediction | 图像预测

## Table of Contents | 目录

- [Function | 函数](#function)
- [Purpose | 用途](#purpose)
- [Parameters | 参数](#parameters)
- [Returns | 返回值](#returns)
- [Example | 示例](#example)
- [Related Documentation | 相关文档](#related-documentation)

## Function | 函数

```cpp
std::string SmartPredictor_predict_img_filter(unsigned char* imageData, long byteSize, float threshold);
```

## Purpose | 用途

Performs prediction/recognition on an image using the loaded model. This function analyzes the input image and returns classification results that meet the specified threshold.
使用加载的模型对图像进行预测/识别。此函数分析输入图像并返回满足指定阈值的分类结果。

## Parameters | 参数

- `imageData`: Image data byte array | 图像数据字节数组

  - Type: `unsigned char*` | 类型: `unsigned char*`
  - Description: Raw image data in bytes | 描述: 原始图像数据（字节格式）
  - Format: JPEG, recommended resolution greater than 400x400 | 格式: JPEG，建议分辨率大于400x400
- `byteSize`: Size of image data | 图像数据大小

  - Type: `long` | 类型: `long`
  - Description: Size of the image data in bytes | 描述: 图像数据的字节大小
  - Note: Must be accurate to prevent buffer overflows | 注意: 必须准确以防止缓冲区溢出
- `threshold`: Prediction threshold | 预测阈值

  - Type: `float` | 类型: `float`
  - Description: Minimum confidence score for predictions. This parameter controls the algorithm's filtering of irrelevant results during recognition. Higher values provide stronger filtering effects. | 描述: 预测的最小置信度分数。此参数控制算法在识别过程中对无关结果的过滤。值越高，过滤效果越强。
  - Range: 0.0 to 1.0 | 范围: 0.0到1.0
  - Recommended: 0.3 | 推荐值: 0.3

## Returns | 返回值

JSON string containing prediction results in the following format:
包含预测结果的JSON字符串，格式如下：

```json
{"scores": 
  [ 
    ["apple", "0.3"], 
    ["orange", "0.2"], 
    ["banana", "0.2"], 
    ["onion", "0.2"], 
    ["tomato", "0.1"] 
  ], 
"predicted_label":" apple" 
} 
```

**Format explanation:**
**格式说明:**

- `scores`: Array of prediction results | 预测结果数组
  - First element: label of item | 第一个元素: 物品标签
  - Second element: confidence score of item | 第二个元素: 物品的置信度分数
- `predicted_label`: The label with highest confidence | 置信度最高的标签

## Example | 示例

```cpp
// Read image file | 读取图像文件
std::vector<unsigned char> imageData = readImage("demo.jpg");

// Perform prediction | 执行预测
std::string result = SmartPredictor_predict_img_filter(
    imageData.data(),
    imageData.size(),
    0.3f
);

// Parse and display results | 解析并显示结果
std::cout << "Prediction results: " << result << std::endl;
```

## Related Documentation | 相关文档

- [Main Documentation | 主文档](../README.md) - Back to main documentation | 返回主文档
- [SDK Authorization | SDK授权](authorization.md) - Required before using prediction | 使用预测功能前必需
- [Model Loading | 模型加载](model_load.md) - Load models before prediction | 预测前加载模型
- [Image Registration | 图像注册](registration.md) - Improve model accuracy with training data | 使用训练数据提高模型准确性
- [Model Management | 模型管理](model_management.md) - Manage model lifecycle | 管理模型生命周期
