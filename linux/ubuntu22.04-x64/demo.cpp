/**
 * @file demo_linux.cpp
 * @brief Image processing and prediction demonstration program (Linux version)
 */

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <stdexcept>
#include <fstream>
#include <dlfcn.h>
#include <unistd.h>
#include <termios.h>
#include <limits.h>

// Configuration parameters
const char* LIB_NAME = "./lib/libsmart_predictor_jni.so";
const char* MODEL_DIR = "./model";
const char* TEST_IMAGE_PATH = "demo.jpg";
float PREDICTION_THRESHOLD = 0.3f;

// Function pointers
void* lib_handle = nullptr;
using SmartPredictor_load = int(*)(const char*, int);
using SmartPredictor_unload = int(*)();
using SmartPredictor_predict_img = int(*)(unsigned char*, long, float, char*, long);
using SmartPredictor_regist_img = int(*)(unsigned char*, long, const char*, int);
using SmartPredictor_save = int(*)(const char*);
using SmartPredictor_reset = bool(*)(const char*);
using SmartPredictor_delete = bool(*)(const char*);
using SmartPredictor_sign = int(*)(const char*, const char*);

SmartPredictor_load load_func = nullptr;
SmartPredictor_unload unload_func = nullptr;
SmartPredictor_predict_img predict_func = nullptr;
SmartPredictor_regist_img regist_func = nullptr;
SmartPredictor_save save_func = nullptr;
SmartPredictor_reset reset_func = nullptr;
SmartPredictor_delete delete_func = nullptr;
SmartPredictor_sign sign_func = nullptr;

// Function declarations
std::vector<unsigned char> readImage(const std::string& filePath);
void displayMenu();
bool loadLibrary();
bool getFunctionPointers();
int getch();

int main() {
    std::cout << "Welcome to Ronsson AI SDK (Linux Version)" << std::endl;
    
    if (!loadLibrary()) {
        std::cerr << "Failed to load library: " << dlerror() << std::endl;
        std::cout << "Press any key to exit..." << std::endl;
        getch();
        return -1;
    }
    
    if (!getFunctionPointers()) {
        std::cerr << "Failed to get all required function pointers" << std::endl;
        std::cout << "Press any key to exit..." << std::endl;
        getch();
        return -1;
    }
    
    bool running = true;
    int choice;
    
    while (running) {
        displayMenu();
        choice = getch();
        
        std::cout << std::endl;
        
        switch (choice) {
            case 'a': {
                // SDK Authorization
                std::cout << "SDK authorization..." << std::endl;
                std::string auth_code;
                std::cout << "Enter authorization code: ";
                std::getline(std::cin, auth_code);
                
                int code = sign_func(MODEL_DIR, auth_code.c_str());
                if (code == 0) {
                    std::cout << "Authorization successful" << std::endl;
                } else {
                    std::cout << "Authorization failed with code: " << code << std::endl;
                }
                break;
            }
            case 'l': {
                // Load Model
                std::cout << "Loading model..." << std::endl;
                if (load_func(MODEL_DIR, 4) < 0) {
                    std::cout << "Failed to load model" << std::endl;
                } else {
                    std::cout << "Model loaded successfully" << std::endl;
                }
                break;
            }
            case 'p': {
                // Predict
                std::cout << "Processing image for prediction..." << std::endl;
                try {
                    std::vector<unsigned char> imageData = readImage(TEST_IMAGE_PATH);
                    char buffer[1024];
                    int predictResult = predict_func(imageData.data(),
                        static_cast<unsigned int>(imageData.size()), 
                        PREDICTION_THRESHOLD,
                        buffer,
                        sizeof(buffer));
                    std::cout << "Prediction result: " << predictResult << std::endl;
                    std::cout << "Prediction content: " << buffer << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Failed to predict image: " << e.what() << std::endl;
                }
                break;
            }
            case 'r': {
                // Register Image
                std::cout << "Enter label for the image: ";
                std::string label;
                std::getline(std::cin, label); 
                try {
                    std::vector<unsigned char> imageData = readImage(TEST_IMAGE_PATH);
                    auto start = std::chrono::high_resolution_clock::now();
                    
                    int registResult = regist_func(imageData.data(), 
                                                  static_cast<unsigned int>(imageData.size()), 
                                                  label.c_str(), 6);
                    
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    
                    std::cout << "Registration time: " << duration.count() << "ms" << std::endl;
                    std::cout << "Registration result: " << registResult << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Failed to register image: " << e.what() << std::endl;
                }
                break;
            }
            case 's': {
                // Save Model
                std::cout << "Saving model..." << std::endl;
                if (save_func(MODEL_DIR) != 1) {
                    std::cout << "Failed to save model" << std::endl;
                } else {
                    std::cout << "Model saved successfully" << std::endl;
                }
                break;
            }
            case 'c': {
                // Clear Model
                std::cout << "Clearing model..." << std::endl;
                if (reset_func(MODEL_DIR)) {
                    std::cout << "Model cleared successfully" << std::endl;
                } else {
                    std::cout << "Failed to clear model" << std::endl;
                }
                break;
            }
            case 'd': {
                // Delete Label
                std::cout << "Enter label to delete: ";
                std::string label_to_delete;
                std::getline(std::cin, label_to_delete);
                
                std::cout << "Deleting label '" << label_to_delete << "'..." << std::endl;
                if (delete_func(label_to_delete.c_str())) {
                    std::cout << "Label deleted successfully" << std::endl;
                } else {
                    std::cout << "Failed to delete label" << std::endl;
                }
                break;
            }
            case 'u': {
                // Unload Model
                std::cout << "Unloading model..." << std::endl;
                if (unload_func() == 0) {
                    std::cout << "Model unloaded successfully" << std::endl;
                } else {
                    std::cout << "Failed to unload model" << std::endl;
                }
                break;
            }
            case 'q': {
                // Quit
                running = false;
                break;
            }
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
        }
        
        if (running) {
            std::cout << std::endl;
            std::cout << "Press any key to continue..." << std::endl;
            getch();
        }
    }
    
    dlclose(lib_handle);
    return 0;
}

void displayMenu() {
    system("clear");
    std::cout << "==== Ronsson AI SDK Tool (Linux) ====" << std::endl;
    std::cout << "Press 'a': SDK Authorization" << std::endl;
    std::cout << "Press 'l': Load Model" << std::endl;
    std::cout << "Press 'p': Predict Image (demo.jpg)" << std::endl;
    std::cout << "Press 'r': Register Image (demo.jpg)" << std::endl;
    std::cout << "Press 's': Save Model" << std::endl;
    std::cout << "Press 'c': Clear Model" << std::endl;
    std::cout << "Press 'd': Delete label from model" << std::endl;
    std::cout << "Press 'u': Unload Model" << std::endl;
    std::cout << "Press 'q': Quit" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "Enter your choice: ";
}

bool loadLibrary() {
    lib_handle = dlopen(LIB_NAME, RTLD_LAZY);
    return lib_handle != nullptr;
}

bool getFunctionPointers() {
    load_func = (SmartPredictor_load)dlsym(lib_handle, "SmartPredictor_load");
    unload_func = (SmartPredictor_unload)dlsym(lib_handle, "SmartPredictor_unload");
    predict_func = (SmartPredictor_predict_img)dlsym(lib_handle, "SmartPredictor_predict_img");
    regist_func = (SmartPredictor_regist_img)dlsym(lib_handle, "SmartPredictor_regist_img");
    save_func = (SmartPredictor_save)dlsym(lib_handle, "SmartPredictor_save");
    reset_func = (SmartPredictor_reset)dlsym(lib_handle, "SmartPredictor_reset");
    delete_func = (SmartPredictor_delete)dlsym(lib_handle, "SmartPredictor_delete");
    sign_func = (SmartPredictor_sign)dlsym(lib_handle, "SmartPredictor_sign");

    return load_func && unload_func && predict_func && regist_func && 
           save_func && reset_func && sign_func && delete_func;
}

std::vector<unsigned char> readImage(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open image file: " + filePath);
    }

    file.seekg(0, std::ios::end);
    std::streamoff fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> buffer(static_cast<size_t>(fileSize));
    file.read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(fileSize));
    
    if (!file) {
        throw std::runtime_error("Failed to read image file: " + filePath);
    }

    return buffer;
}

// Linux implementation of getch()
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
