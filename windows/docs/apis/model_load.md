# Model Loading

## Table of Contents

- [Function](#function)
- [Purpose](#purpose)
- [Parameters](#parameters)
- [Returns](#returns)
- [Example](#example)
- [Notes](#notes)
- [Related Documentation](#related-documentation)

## Function

```cpp
int SmartPredictor_load(const std::string& model_dir, int model_type);
```

## Purpose

Loads the AI model from the specified path. This function must be called after successful authorization and before performing any predictions or registrations.

## Parameters

- `model_dir`: Model file path
  - Type: `std::string`
  - Description: Path to the model directory
  - Example: `"./model"`

- `model_type`: Model type
  - Type: `int`
  - Description: Type identifier for the model
  - Value: `4` (for fresh food classification)

## Returns

- `>= 0`: Load successful (returns model handle)
- `< 0`: Load failed

## Example

```cpp
// Load the model
int modelHandle = SmartPredictor_load("./model", 4);
if (modelHandle < 0) {
    std::cerr << "Failed to load model with error code: " << modelHandle << std::endl;
    return;
}
```


## Related Documentation

- [Main Documentation](../README.md) - Back to main documentation
- [SDK Authorization](authorization.md) - Required before loading models
- [Image Prediction](prediction.md) - Use loaded models for classification
- [Image Registration](registration.md) - Add training data to loaded models
- [Model Management](model_management.md) - Save and manage loaded models
