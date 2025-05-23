# Image Prediction

## Table of Contents

- [Function](#function)
- [Purpose](#purpose)
- [Parameters](#parameters)
- [Returns](#returns)
- [Example](#example)
- [Related Documentation](#related-documentation)

## Function

```cpp
std::string SmartPredictor_predict_img_filter(unsigned char* imageData, long byteSize, float threshold);
```

## Purpose

Performs prediction/recognition on an image using the loaded model. This function analyzes the input image and returns classification results that meet the specified threshold.

## Parameters

- `imageData`: Image data byte array
  - Type: `unsigned char*`
  - Description: Raw image data in bytes
  - Format: JPEG, recommended resolution greater than 400x400

- `byteSize`: Size of image data
  - Type: `long`
  - Description: Size of the image data in bytes
  - Note: Must be accurate to prevent buffer overflows

- `threshold`: Prediction threshold
  - Type: `float`
  - Description: Minimum confidence score for predictions. This parameter controls the algorithm's filtering of irrelevant results during recognition. Higher values provide stronger filtering effects.
  - Range: 0.0 to 1.0
  - Recommended: 0.3

## Returns

JSON string containing prediction results in the following format:
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
- `scores`: Array of prediction results
  - First element: label of item 
  - Second element: confidence score of item 
- `predicted_label`: The label with highest confidence

## Example

```cpp
// Read image file
std::vector<unsigned char> imageData = readImage("demo.jpg");

// Perform prediction
std::string result = SmartPredictor_predict_img_filter(
    imageData.data(),
    imageData.size(),
    0.3f
);

// Parse and display results
std::cout << "Prediction results: " << result << std::endl;
```

## Related Documentation

- [Main Documentation](../README.md) - Back to main documentation
- [SDK Authorization](authorization.md) - Required before using prediction
- [Model Loading](model_load.md) - Load models before prediction
- [Image Registration](registration.md) - Improve model accuracy with training data
- [Model Management](model_management.md) - Manage model lifecycle