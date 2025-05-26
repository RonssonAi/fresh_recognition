# Model Management

## Table of Contents

- [Save Model](#save-model)
- [Reset Model](#reset-model)
- [Delete Label](#delete-label)
- [Unload Model](#unload-model)
- [Examples](#examples)
- [Related Documentation](#related-documentation)

This document covers the model management APIs including saving, resetting, and deleting operations.

## Save Model

### Function
```cpp
int SmartPredictor_save(const std::string model_dir);
```

### Purpose
- Saves the model to the disk. It is recommended to save the model when the system is idle or after a certain number of registrations. 
- Saving the model to the disk requires a lot of disk I/O. It is recommended to save when the system is idle or after a certain amount of REGIST; for example, calling once after accumulative 30 times of REGIST. 

### Parameters
- `model_dir`: Model save path
  - Type: `std::string`
  - Description: Path where the model will be saved
  - Example: `"./model"`

### Returns
- `>= 0`: Save successful
- `< 0`: Save failed

## Reset Model

### Function
```cpp
bool SmartPredictor_reset(const std::string model_dir);
```

### Purpose
Clears all data from the model. This operation is irreversible.

### Parameters
- `model_dir`: Model save path
  - Type: `std::string`
  - Description: Path where the model will be saved
  - Example: `"./model"`

### Returns
- `true`: Reset successful
- `false`: Reset failed

## Delete Label

### Function
```cpp
bool SmartPredictor_delete(const std::string label);
```

### Purpose
Deletes all image data associated with the specified label from the model.

### Parameters
- `label`: Label name to delete
  - Type: `std::string`
  - Description: Name of the category to remove
  - Example: `"apple"`

### Returns
- `true`: Deletion successful
- `false`: Deletion failed

## Unload Model

### Function
```cpp
int SmartPredictor_unload();
```

### Purpose
Releases resources of the loaded model. 

### Parameters
None

### Returns
- `0`: Unload successful
- Other values: Unload failed

## Examples

### Save Model
```cpp
// Save model after modifications
if (SmartPredictor_save("./model") < 0) {
    std::cerr << "Failed to save model" << std::endl;
    return;
}
```

### Reset Model
```cpp
// Reset model (irreversible)
if (!SmartPredictor_reset("./model")) {
    std::cerr << "Failed to reset model" << std::endl;
    return;
}
```

### Delete Label
```cpp
// Delete a specific label
if (!SmartPredictor_delete("apple")) {
    std::cerr << "Failed to delete label" << std::endl;
    return;
}
```

### Unload Model
```cpp
// Release model resources
if (SmartPredictor_unload() != 0) {
    std::cerr << "Failed to release model" << std::endl;
    return;
}
```

## Related Documentation

- [Main Documentation](../README.md) - Back to main documentation
- [SDK Authorization](authorization.md) - Required before using model management
- [Model Loading](model_load.md) - Load models before management operations
- [Image Registration](registration.md) - Register data before saving models
- [Image Prediction](prediction.md) - Use models for classification 