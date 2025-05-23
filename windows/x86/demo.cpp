/**
 * @file demo.cpp
 * @brief Image processing and prediction demonstration program
 */

#define NOMINMAX  // Prevent Windows from defining min/max macros

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <stdexcept>
#include <fstream>
#include <conio.h>
#include <limits>

// Configuration parameters
const wchar_t* DLL_NAME = L"smart_predictor_jni.dll";
const char* MODEL_DIR = "./model";
const char* TEST_IMAGE_PATH = "demo.jpg";
float PREDICTION_THRESHOLD = 0.3f;


// DLL function pointers
HINSTANCE dll_handle = nullptr;
using SmartPredictor_load = int(CALLBACK*)(const std::string&, int);
using SmartPredictor_release = int(CALLBACK*)();
using SmartPredictor_predict_img = std::string(CALLBACK*)(unsigned char*, long, float);
using SmartPredictor_regist_img = int(CALLBACK*)(unsigned char*, long byte_size, std::string label, int pos);
using SmartPredictor_save = int(CALLBACK*)(const std::string);
using SmartPredictor_reset = bool(CALLBACK*)(const std::string);
using SmartPredictor_delete = bool(CALLBACK*)(const std::string);
using SmartPredictor_sign = int(CALLBACK*)(const std::string, const std::string);

// Function pointers
SmartPredictor_load load_func = nullptr;
SmartPredictor_release release_func = nullptr;
SmartPredictor_predict_img predict_func = nullptr;
SmartPredictor_regist_img regist_func = nullptr;
SmartPredictor_save save_func = nullptr;
SmartPredictor_reset reset_func = nullptr;
SmartPredictor_delete delete_func = nullptr;
SmartPredictor_sign sign_func = nullptr;

// External function declaration
std::vector<unsigned char> readImage(const std::string& filePath);
void displayMenu();
bool loadDLL();
bool getFunctionPointers();

int main() {
    SetDllDirectoryW(L"lib");
    
    std::cout << "Welcome to Ronsson AI SDK" << std::endl;
    
    if (!loadDLL()) {
        std::cerr << "Failed to load DLL" << std::endl;
        std::cout << "Press any key to exit..." << std::endl;
        _getch();
        return -1;
    }
    
    if (!getFunctionPointers()) {
        std::cerr << "Failed to get all required function pointers" << std::endl;
        std::cout << "Press any key to exit..." << std::endl;
        _getch();
        return -1;
    }
    
    bool running = true;
    int choice;
    
    while (running) {
        displayMenu();
        choice = _getch();
        
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
                    std::string predictResult = predict_func(imageData.data(), 
                                                             static_cast<unsigned int>(imageData.size()), 
                                                             PREDICTION_THRESHOLD);
                    std::cout << "Prediction result: " << predictResult << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Failed to predict image: " << e.what() << std::endl;
                }
                break;
            }
            case 'r': {
                // Register Image
                std::cout << "Enter label for the image: ";
                std::string label;
                std::cin >> label;
                
                try {
                    std::vector<unsigned char> imageData = readImage(TEST_IMAGE_PATH);
                    auto start = std::chrono::high_resolution_clock::now();
                    
                    int registResult = regist_func(imageData.data(), 
                                                  static_cast<unsigned int>(imageData.size()), 
                                                  label.c_str(),6);
                    
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
                std::cin >> label_to_delete;
                
                std::cout << "Deleting label '" << label_to_delete << "'..." << std::endl;
                if (delete_func(label_to_delete.c_str()) == true) {
                    std::cout << "Label deleted successfully" << std::endl;
                } else {
                    std::cout << "Failed to delete label" << std::endl;
                }
                break;
            }
            case 'u': {
                // Unload Model
                std::cout << "Unloading model..." << std::endl;
                if (release_func() == 1) {
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
        }
    }
    
    FreeLibrary(dll_handle);
    return 0;
}

void displayMenu() {
    // system("cls");
    std::cout << "==== Ronsson AI SDK Tool ====" << std::endl;
    std::cout << "Press 'a': SDK Authorization" << std::endl;
    std::cout << "Press 'l': Load Model" << std::endl;
    std::cout << "Press 'p': Predict Image (demo.jpg)" << std::endl;
    std::cout << "Press 'r': Register Image (demo.jpg)" << std::endl;
    std::cout << "Press 's': Save Model" << std::endl;
    std::cout << "Press 'c': Clear Model" << std::endl;
    std::cout << "Press 'd': Delete all pictures of label in model" << std::endl;
    std::cout << "Press 'u': Unload Model" << std::endl;
    std::cout << "Press 'q': Quit" << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << "Enter your choice: ";
}

bool loadDLL() {
    dll_handle = LoadLibraryW(DLL_NAME);
    return dll_handle != nullptr;
}

bool getFunctionPointers() {
    load_func = (SmartPredictor_load)GetProcAddress(dll_handle, "SmartPredictor_load");
    release_func = (SmartPredictor_release)GetProcAddress(dll_handle, "SmartPredictor_release");
    predict_func = (SmartPredictor_predict_img)GetProcAddress(dll_handle, "SmartPredictor_predict_img_filter");
    regist_func = (SmartPredictor_regist_img)GetProcAddress(dll_handle, "SmartPredictor_regist_img");
    save_func = (SmartPredictor_save)GetProcAddress(dll_handle, "SmartPredictor_save");
    reset_func = (SmartPredictor_reset)GetProcAddress(dll_handle, "SmartPredictor_reset");
    delete_func = (SmartPredictor_delete)GetProcAddress(dll_handle, "SmartPredictor_delete");
    sign_func = (SmartPredictor_sign)GetProcAddress(dll_handle, "SmartPredictor_sign");

    return load_func && release_func && predict_func && regist_func && 
           save_func && reset_func && sign_func && delete_func;
}

// read image file
std::vector<unsigned char> readImage(const std::string& filePath) {
    // Open file in binary mode
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open image file: " + filePath);
    }

    // Get file size
    file.seekg(0, std::ios::end);
    std::streamoff fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read file content
    std::vector<unsigned char> buffer(static_cast<size_t>(fileSize));
    file.read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(fileSize));
    
    if (!file) {
        throw std::runtime_error("Failed to read image file: " + filePath);
    }

    return buffer;
} 