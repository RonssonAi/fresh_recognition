# SDK Authorization | SDK授权

## Table of Contents | 目录

- [Function | 函数](#function)
- [Purpose | 用途](#purpose)
- [Parameters | 参数](#parameters)
- [Returns | 返回值](#returns)
- [Error Codes | 错误代码](#error-codes)
- [Example | 示例](#example)
- [Implementation Notes | 实现说明](#implementation-notes)
- [Troubleshooting | 故障排除](#troubleshooting)
- [Related Documentation | 相关文档](#related-documentation)

## Function | 函数

```cpp
int SmartPredictor_sign(const std::string model_dir, const std::string auth_code);
```

## Purpose | 用途

Performs SDK authorization verification. Authorization must be completed first before using any other SDK features.
执行SDK授权验证。在使用任何其他SDK功能之前，必须先完成授权。

- If you want to provide an authorization interface in your own software, you need to call this function.
- 如果您想在自己的软件中提供授权接口，需要调用此函数。
- Alternatively, you can use the built-in demo.exe to perform SDK authorization.
- 或者，您可以使用内置的demo.exe来执行SDK授权。

## Parameters | 参数

- `model_dir`: Path to the model directory | 模型目录路径
  - Type: `std::string`
  - Description: The directory where model files are stored |存储模型文件的目录
  - Example: `"./model"`

- `auth_code`: Authorization code | 授权码
  - Type: `std::string`
  - Description: Unique authorization code for your terminal | 终端的唯一授权码
  - Note: One authorization code can only be used on one terminal | 注意: 一个授权码只能在一台终端上使用

## Returns | 返回值

- `0`: Authorization successful | 授权成功
- Other values: Authorization failed (see error codes below)| 其他值: 授权失败（参见下面的错误代码）

## Error Codes | 错误代码

### Network Related Errors | 网络相关错误
- `-101`: Network initialization error | 网络初始化错误
- `-102`: Network connection error | 网络连接错误
- `-103`: Failed to get network response | 获取网络响应失败
- `-104`: Invalid online response format | 无效的在线响应格式
- `-105`: Invalid online response format | 无效的在线响应格式
- `-106`: Invalid online response format | 无效的在线响应格式

### Registration Response Errors | 注册响应错误
- `-107`: Invalid or expired registration code | 无效或过期的注册码
- `-108`: Online registration response format error | 在线注册响应格式错误
- `-109`: Online registration response format error | 在线注册响应格式错误
- `-110`: Online registration response format error | 在线注册响应格式错误
- `-111`: Online registration response format error | 在线注册响应格式错误
- `-112`: Online registration response format error | 在线注册响应格式错误
- `-113`: Online registration response format error, store list is empty | 在线注册响应格式错误，商店列表为空

### Signature Related Errors | 签名相关错误
- `-201`: Signature error or missing critical information | 签名错误或缺少关键信息
- `-202`: Signature error or missing critical information | 签名错误或缺少关键信息
- `-203`: Signature error or missing critical information | 签名错误或缺少关键信息
- `-204`: Signature error or missing critical information | 签名错误或缺少关键信息
- `-205`: Signature error or missing critical information | 签名错误或缺少关键信息
- `-206`: Signature error or missing critical information | 签名错误或缺少关键信息
- `-207`: Signature error or missing critical information | 签名错误或缺少关键信息
- `-208`: Signature error or missing critical information | 签名错误或缺少关键信息

### File Write Errors | 文件写入错误
- `-301`: Failed to create signature file, path or permission error | 创建签名文件失败，路径或权限错误
- `-302`: Failed to write signature file data, path or permission error | 写入签名文件数据失败，路径或权限错误

### File Read Errors | 文件读取错误
- `-401`: Failed to open signature file, file not found or permission error | 打开签名文件失败，文件未找到或权限错误
- `-402`: Failed to read signature file data, data corruption or permission error | 读取签名文件数据失败，数据损坏或权限错误

### Signature File Errors | 签名文件错误
- `-501`: Signature file does not exist or insufficient read permissions | 签名文件不存在或读取权限不足
- `-502`: Signature file format error or missing critical information | 签名文件格式错误或缺少关键信息
- `-503`: Signature file format error or missing critical information | 签名文件格式错误或缺少关键信息
- `-504`: Signature file format error or missing critical information | 签名文件格式错误或缺少关键信息
- `-505`: Signature file format error or missing critical information | 签名文件格式错误或缺少关键信息
- `-506`: Failed to get UUID | 获取UUID失败
- `-507`: Invalid UUID | 无效的UUID
- `-508`: Registration code has expired | 注册码已过期

## Example | 示例

```cpp
// Initialize SDK with authorization
// 使用授权初始化SDK
int authResult = SmartPredictor_sign("./model", "your_auth_code");
if (authResult != 0) {
    std::cerr << "Authorization failed with code: " << authResult << std::endl;
    return;
}
std::cout << "Authorization successful!" << std::endl;
```

## Implementation Notes | 实现说明

1. **Mandatory Step**: Authorization is required before using any SDK features
   **必要步骤**: 在使用任何SDK功能之前都需要授权
2. **Unique Binding**: Each authorization code is unique to one terminal/device
   **唯一绑定**: 每个授权码仅对应一个终端/设备
3. **Security**: Keep your authorization code secure and do not share it
   **安全性**: 请妥善保管您的授权码，不要分享给他人
4. **File Permissions**: Ensure the application has read/write permissions in the model directory
   **文件权限**: 确保应用程序在模型目录中具有读写权限
5. **Network Requirements**: Internet connection is required for initial authorization
   **网络要求**: 初始授权需要互联网连接

## Troubleshooting | 故障排除

### Common Issues | 常见问题
- **Network errors (-101 to -103)**: Check internet connection and firewall settings
  **网络错误(-101到-103)**: 检查互联网连接和防火墙设置
- **Registration errors (-107 to -113)**: Verify authorization code validity and format
  **注册错误(-107到-113)**: 验证授权码的有效性和格式
- **File permission errors (-301, -302, -401, -402)**: Check directory permissions
  **文件权限错误(-301, -302, -401, -402)**: 检查目录权限
- **Signature file errors (-501 to -508)**: Delete existing signature files and re-authorize
  **签名文件错误(-501到-508)**: 删除现有签名文件并重新授权

### Support | 支持
For authorization code requests or technical support, contact: chenbuqiao@qq.com
如需授权码或技术支持，请联系：chenbuqiao@qq.com

## Related Documentation | 相关文档

- [Main Documentation | 主文档](../README.md) - Back to main documentation | 返回主文档
- [Model Loading API | 模型加载API](model_load.md) - Load models after authorization | 授权后加载模型
- [Image Prediction API | 图像预测API](prediction.md) - Perform image classification | 执行图像分类
- [Image Registration API | 图像注册API](registration.md) - Register training data | 注册训练数据
- [Model Management API | 模型管理API](model_management.md) - Manage model lifecycle | 管理模型生命周期 