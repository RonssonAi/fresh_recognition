# 安装说明

## 系统要求

- C++11 或更高版本
- OpenCV 4.x
- CMake 3.10 或更高版本
- Android NDK (如果需要在 Android 平台使用)

## 安装步骤

### 1. 安装依赖

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake
sudo apt-get install -y libopencv-dev
```

#### CentOS/RHEL
```bash
sudo yum groupinstall "Development Tools"
sudo yum install cmake
sudo yum install opencv-devel
```

### 2. 编译安装

```bash
# 创建构建目录
mkdir build && cd build

# 配置项目
cmake ..

# 编译
make -j4

# 安装
sudo make install
```

### 3. 配置环境变量

将以下内容添加到 `~/.bashrc` 或 `~/.zshrc`：

```bash
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```

### 4. 验证安装

```bash
# 检查库文件是否正确安装
ldconfig -p | grep libsmart_predictor

# 运行测试程序
./test_linux
```

## 常见问题

### 1. 找不到 OpenCV

如果遇到找不到 OpenCV 的问题，请确保：
- OpenCV 已正确安装
- 环境变量已正确设置
- CMake 能找到 OpenCV 的安装路径

### 2. 编译错误

如果遇到编译错误：
- 检查是否满足所有系统要求
- 确保所有依赖都已正确安装
- 检查 CMake 配置是否正确

### 3. 运行时错误

如果遇到运行时错误：
- 检查库文件是否正确安装
- 检查环境变量是否正确设置
- 检查模型文件是否存在且可访问

## 下一步

安装完成后，请参考[快速开始](quickstart.md)了解如何使用系统。 