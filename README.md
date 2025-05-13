# SmartPredictor 图像识别系统

SmartPredictor 是一个简单易用的图像识别系统，支持图像注册和预测功能。

## 快速开始

### 安装

```bash
pip install smartpredictor
```

### 基本使用

```python
from smartpredictor import SmartPredictor

# 初始化预测器
predictor = SmartPredictor()

# 注册图像
predictor.register("image1.jpg", "类别1")
predictor.register("image2.jpg", "类别2")

# 预测图像
result = predictor.predict("test.jpg")
print(f"预测结果: {result}")
```

## 主要功能

- 图像注册：支持批量注册图像
- 图像预测：快速识别图像类别
- 模型保存：支持保存和加载模型

## API 说明

### 初始化
```python
predictor = SmartPredictor(model_path="path/to/model")
```

### 注册图像
```python
predictor.register(image_path, label)
```

### 预测图像
```python
result = predictor.predict(image_path)
```

### 保存模型
```python
predictor.save("model.pkl")
```

## 示例代码

### 基础示例
```python
from smartpredictor import SmartPredictor

# 创建预测器实例
predictor = SmartPredictor()

# 注册训练图像
predictor.register("train/apple1.jpg", "apple")
predictor.register("train/banana1.jpg", "banana")

# 预测新图像
result = predictor.predict("test/fruit.jpg")
print(f"预测结果: {result}")
```

## 常见问题

1. Q: 支持哪些图像格式？
   A: 支持 JPG、PNG、BMP 等常见图像格式。

2. Q: 如何提高识别准确率？
   A: 建议使用清晰的图像，并确保训练图像具有代表性。

## 联系方式

- GitHub: [RonssonAi/fresh_recognition](https://github.com/RonssonAi/fresh_recognition) 