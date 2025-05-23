# Image Registration

## Table of Contents

- [Function](#function)
- [Purpose](#purpose)
- [Parameters](#parameters)
- [Returns](#returns)
- [Example](#example)
- [Related Documentation](#related-documentation)

## Function

```cpp
int SmartPredictor_regist_img(unsigned char* imageData, long byteSize, std::string label, int pos);
```

## Purpose

Registers a new image and its label to the model. This function is used to add new training data to improve the model's recognition capabilities.

## Parameters

- `imageData`: Image data byte array
  - Type: `unsigned char*`
  - Description: Raw image data in bytes
  - Format: JPEG, PNG, or BMP

- `byteSize`: Size of image data
  - Type: `long`
  - Description: Size of the image data in bytes
  - Note: Must be accurate to prevent buffer overflows

- `label`: Image label
  - Type: `std::string`
  - Description: Category or class name for the image
  - Example: `"apple"`, `"banana"`

- `pos`: position/index, 
  - Type: `int`
  - Description: The ranking of the item for prediction. value from 1 to 6. After each predict, the user interface selects the result and records the index. You can then call regist with the index passed in from 1-6. If the user did not select a result for predict, pass in 6. This parameter is used to optimize the effect of the algorithm. 
  - Value: `optional range [1-6]` 

## Returns

- `0`: Registration successful
- Other values: Registration failed


## Example

```cpp
// Read image file
std::vector<unsigned char> imageData = readImage("apple.jpg");

// Register the image
int result = SmartPredictor_regist_img(
    imageData.data(),
    imageData.size(),
    "apple",
    6
);

if (result != 0) {
    std::cerr << "Registration failed with code: " << result << std::endl;
    return;
}

```

## Related Documentation

- [Main Documentation](../README.md) - Back to main documentation
- [SDK Authorization](authorization.md) - Required before using registration
- [Model Loading](model_load.md) - Load models before registration
- [Image Prediction](prediction.md) - Use prediction results to guide registration
- [Model Management](model_management.md) - Save registered data and manage models 