# 基础示例

本文档提供了 SmartPredictor 的基本使用示例，帮助您快速上手。

## 1. 基本使用流程

```cpp
#include <iostream>
#include <string>
#include <fstream>

int main() {
    // 1. 加载模型
    std::string model_dir = "path/to/model";
    int result = SmartPredictor_load(model_dir);
    if (result != 0) {
        std::cerr << "模型加载失败: " << result << std::endl;
        return 1;
    }

    // 2. 读取图像
    std::string image_path = "test.jpg";
    std::ifstream fin(image_path, std::ios::binary);
    if (!fin.is_open()) {
        std::cerr << "无法打开图像文件" << std::endl;
        return 1;
    }
    
    // 获取文件大小
    fin.seekg(0, std::ios::end);
    int file_size = fin.tellg();
    fin.seekg(0, std::ios::beg);
    
    // 读取图像数据
    unsigned char* img_bytes = new unsigned char[file_size];
    fin.read((char*)img_bytes, file_size);
    fin.close();

    // 3. 注册图像
    std::string label = "apple";
    result = SmartPredictor_regist_img(img_bytes, file_size, label);
    if (result < 0) {
        std::cerr << "图像注册失败: " << result << std::endl;
        delete[] img_bytes;
        return 1;
    }
    std::cout << "图像注册成功，样本ID: " << result << std::endl;

    // 4. 预测图像
    float similarity_threshold = 0.6;
    std::string prediction = SmartPredictor_predict_img_filter(img_bytes, file_size, similarity_threshold);
    std::cout << "预测结果: " << prediction << std::endl;

    // 5. 保存模型
    result = SmartPredictor_save(model_dir);
    if (result != 1) {
        std::cerr << "模型保存失败: " << result << std::endl;
        delete[] img_bytes;
        return 1;
    }

    // 6. 清理资源
    delete[] img_bytes;
    return 0;
}
```

## 2. 错误处理示例

```cpp
// 错误处理函数
void handle_error(int error_code, const std::string& operation) {
    switch (error_code) {
        case -1:
            std::cerr << operation << "失败: 模型加载错误" << std::endl;
            break;
        case -2:
            std::cerr << operation << "失败: 图像注册错误" << std::endl;
            break;
        case -3:
            std::cerr << operation << "失败: 预测错误" << std::endl;
            break;
        case -4:
            std::cerr << operation << "失败: 保存错误" << std::endl;
            break;
        default:
            std::cerr << operation << "失败: 未知错误 " << error_code << std::endl;
    }
}

// 使用示例
int result = SmartPredictor_load(model_dir);
if (result != 0) {
    handle_error(result, "模型加载");
    return 1;
}
```

## 3. 批量处理示例

```cpp
// 批量注册图像
void batch_register_images(const std::vector<std::string>& image_paths, 
                         const std::string& label) {
    for (const auto& path : image_paths) {
        // 读取图像
        std::ifstream fin(path, std::ios::binary);
        if (!fin.is_open()) {
            std::cerr << "无法打开图像: " << path << std::endl;
            continue;
        }

        // 获取文件大小
        fin.seekg(0, std::ios::end);
        int file_size = fin.tellg();
        fin.seekg(0, std::ios::beg);

        // 读取图像数据
        unsigned char* img_bytes = new unsigned char[file_size];
        fin.read((char*)img_bytes, file_size);
        fin.close();

        // 注册图像
        int result = SmartPredictor_regist_img(img_bytes, file_size, label);
        if (result < 0) {
            std::cerr << "图像注册失败: " << path << std::endl;
        } else {
            std::cout << "图像注册成功: " << path << ", ID: " << result << std::endl;
        }

        delete[] img_bytes;
    }
}
```

## 4. 性能优化示例

```cpp
#include <thread>
#include <vector>
#include <queue>
#include <mutex>

// 线程安全的图像处理队列
class ImageProcessQueue {
private:
    std::queue<std::pair<unsigned char*, int>> queue;
    std::mutex mtx;

public:
    void push(unsigned char* img, int size) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push({img, size});
    }

    bool pop(unsigned char*& img, int& size) {
        std::lock_guard<std::mutex> lock(mtx);
        if (queue.empty()) return false;
        img = queue.front().first;
        size = queue.front().second;
        queue.pop();
        return true;
    }
};

// 多线程处理示例
void process_images_thread(ImageProcessQueue& queue) {
    unsigned char* img;
    int size;
    while (queue.pop(img, size)) {
        // 处理图像
        std::string prediction = SmartPredictor_predict_img_filter(img, size, 0.6);
        std::cout << "预测结果: " << prediction << std::endl;
        delete[] img;
    }
}
```

## 5. 完整应用示例

```cpp
class SmartPredictorApp {
private:
    std::string model_dir;
    bool is_model_loaded;

public:
    SmartPredictorApp(const std::string& model_path) 
        : model_dir(model_path), is_model_loaded(false) {}

    bool initialize() {
        int result = SmartPredictor_load(model_dir);
        if (result != 0) {
            std::cerr << "初始化失败: " << result << std::endl;
            return false;
        }
        is_model_loaded = true;
        return true;
    }

    int register_image(const std::string& image_path, const std::string& label) {
        if (!is_model_loaded) {
            std::cerr << "模型未加载" << std::endl;
            return -1;
        }

        // 读取图像
        std::ifstream fin(image_path, std::ios::binary);
        if (!fin.is_open()) {
            std::cerr << "无法打开图像: " << image_path << std::endl;
            return -1;
        }

        fin.seekg(0, std::ios::end);
        int file_size = fin.tellg();
        fin.seekg(0, std::ios::beg);

        unsigned char* img_bytes = new unsigned char[file_size];
        fin.read((char*)img_bytes, file_size);
        fin.close();

        int result = SmartPredictor_regist_img(img_bytes, file_size, label);
        delete[] img_bytes;
        return result;
    }

    std::string predict_image(const std::string& image_path, float threshold = 0.6) {
        if (!is_model_loaded) {
            std::cerr << "模型未加载" << std::endl;
            return "";
        }

        // 读取图像
        std::ifstream fin(image_path, std::ios::binary);
        if (!fin.is_open()) {
            std::cerr << "无法打开图像: " << image_path << std::endl;
            return "";
        }

        fin.seekg(0, std::ios::end);
        int file_size = fin.tellg();
        fin.seekg(0, std::ios::beg);

        unsigned char* img_bytes = new unsigned char[file_size];
        fin.read((char*)img_bytes, file_size);
        fin.close();

        std::string result = SmartPredictor_predict_img_filter(img_bytes, file_size, threshold);
        delete[] img_bytes;
        return result;
    }

    bool save_model() {
        if (!is_model_loaded) {
            std::cerr << "模型未加载" << std::endl;
            return false;
        }

        int result = SmartPredictor_save(model_dir);
        return result == 1;
    }

    ~SmartPredictorApp() {
        if (is_model_loaded) {
            save_model();
        }
    }
};
```

## 下一步

- 查看[高级用法](advanced.md)了解更多高级特性
- 参考[API文档](../api/overview.md)了解完整的API说明
- 查看[常见问题](../faq.md)获取更多帮助 