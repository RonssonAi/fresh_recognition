# SDK Authorization

## Table of Contents

- [Function](#function)
- [Purpose](#purpose)
- [Parameters](#parameters)
- [Returns](#returns)
- [Error Codes](#error-codes)
- [Example](#example)
- [Implementation Notes](#implementation-notes)
- [Troubleshooting](#troubleshooting)
- [Related Documentation](#related-documentation)

## Function

```cpp
int SmartPredictor_sign(const std::string model_dir, const std::string auth_code);
```

## Purpose

Performs SDK authorization verification. Authorization must be completed first before using any other SDK features.

- If you want to provide an authorization interface in your own software, you need to call this function. 
- Alternatively, you can use the built-in demo.exe to perform SDK authorization.

## Parameters

- `model_dir`: Path to the model directory
  - Type: `std::string`
  - Description: The directory where model files are stored
  - Example: `"./model"`

- `auth_code`: Authorization code
  - Type: `std::string`
  - Description: Unique authorization code for your terminal
  - Note: One authorization code can only be used on one terminal

## Returns

- `0`: Authorization successful
- Other values: Authorization failed (see error codes below)

## Error Codes

### Network Related Errors
- `-101`: Network initialization error
- `-102`: Network connection error
- `-103`: Failed to get network response
- `-104`: Invalid online response format
- `-105`: Invalid online response format
- `-106`: Invalid online response format

### Registration Response Errors
- `-107`: Invalid or expired registration code
- `-108`: Online registration response format error
- `-109`: Online registration response format error
- `-110`: Online registration response format error
- `-111`: Online registration response format error
- `-112`: Online registration response format error
- `-113`: Online registration response format error, store list is empty

### Signature Related Errors
- `-201`: Signature error or missing critical information
- `-202`: Signature error or missing critical information
- `-203`: Signature error or missing critical information
- `-204`: Signature error or missing critical information
- `-205`: Signature error or missing critical information
- `-206`: Signature error or missing critical information
- `-207`: Signature error or missing critical information
- `-208`: Signature error or missing critical information

### File Write Errors
- `-301`: Failed to create signature file, path or permission error
- `-302`: Failed to write signature file data, path or permission error

### File Read Errors
- `-401`: Failed to open signature file, file not found or permission error
- `-402`: Failed to read signature file data, data corruption or permission error

### Signature File Errors
- `-501`: Signature file does not exist or insufficient read permissions
- `-502`: Signature file format error or missing critical information
- `-503`: Signature file format error or missing critical information
- `-504`: Signature file format error or missing critical information
- `-505`: Signature file format error or missing critical information
- `-506`: Failed to get UUID
- `-507`: Invalid UUID
- `-508`: Registration code has expired

## Example

```cpp
// Initialize SDK with authorization
int authResult = SmartPredictor_sign("./model", "your_auth_code");
if (authResult != 0) {
    std::cerr << "Authorization failed with code: " << authResult << std::endl;
    return;
}
std::cout << "Authorization successful!" << std::endl;
```

## Implementation Notes

1. **Mandatory Step**: Authorization is required before using any SDK features
2. **Unique Binding**: Each authorization code is unique to one terminal/device
3. **Security**: Keep your authorization code secure and do not share it
4. **File Permissions**: Ensure the application has read/write permissions in the model directory
5. **Network Requirements**: Internet connection is required for initial authorization

## Troubleshooting

### Common Issues
- **Network errors (-101 to -103)**: Check internet connection and firewall settings
- **Registration errors (-107 to -113)**: Verify authorization code validity and format
- **File permission errors (-301, -302, -401, -402)**: Check directory permissions
- **Signature file errors (-501 to -508)**: Delete existing signature files and re-authorize

### Support
For authorization code requests or technical support, contact: chenbuqiao@qq.com

## Related Documentation

- [Main Documentation](../README.md) - Back to main documentation
- [Model Loading API](model_load.md) - Load models after authorization
- [Image Prediction API](prediction.md) - Perform image classification
- [Image Registration API](registration.md) - Register training data
- [Model Management API](model_management.md) - Manage model lifecycle 