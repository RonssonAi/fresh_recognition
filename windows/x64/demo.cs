using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;

namespace TestPredicotr
{
    class Class1
    {
        // 配置参数
        private const string DLL_NAME = "smart_predictor_jni.dll";
        private const string MODEL_DIR = "./model";
        private const string TEST_IMAGE_PATH = "demo.jpg";
        private static float PREDICTION_THRESHOLD = 0.3f;


        // 导入 SetDllDirectory 函数
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        private static extern bool SetDllDirectory(string lpPathName);

        // 确保调用约定和参数类型正确
        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        private static extern int SmartPredictor_load(
            [MarshalAs(UnmanagedType.LPStr)] string modelDir,
            int param);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        private static extern int SmartPredictor_unload();

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        private static extern int SmartPredictor_predict_img_filter(
            byte[] imageData,
            int byteSize,
            float threshold,
            byte[] buffer,
            int bufferSize);

        [DllImport(DLL_NAME,CallingConvention = CallingConvention.Cdecl,ExactSpelling = true)]
        public static extern int SmartPredictor_regist_img(
            byte[] imageData,
            int byteSize,
            [MarshalAs(UnmanagedType.LPStr)] string label,
            int pos
        );

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        private static extern int SmartPredictor_save(
            [MarshalAs(UnmanagedType.LPStr)] string modelDir);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool SmartPredictor_reset(
            [MarshalAs(UnmanagedType.LPStr)] string modelDir);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool SmartPredictor_delete(
            [MarshalAs(UnmanagedType.LPStr)] string label);


        [DllImport(DLL_NAME,CallingConvention = CallingConvention.Cdecl,ExactSpelling = true)]
        public static extern int SmartPredictor_sign(
            [MarshalAs(UnmanagedType.LPStr)] string model_dir,
            [MarshalAs(UnmanagedType.LPStr)] string auth_code
        );


        // 辅助函数：从非托管内存中获取字符串
        private static string PtrToStringUtf8(IntPtr ptr)
        {
            if (ptr == IntPtr.Zero)
                return string.Empty;

            // 计算字符串长度
            int len = 0;
            while (Marshal.ReadByte(ptr, len) != 0)
                len++;

            // 分配托管内存并复制字符串
            byte[] buffer = new byte[len];
            Marshal.Copy(ptr, buffer, 0, len);
            return Encoding.UTF8.GetString(buffer);
        }

        static void Main(string[] args)
        {
            // 设置 DLL 搜索路径为 "lib" 目录
            bool success = SetDllDirectory("lib");
            if (!success)
            {
                int errorCode = Marshal.GetLastWin32Error();
                Console.WriteLine($"SetDllDirectory failed with error code: {errorCode}");
            }
            else
            {
                Console.WriteLine("SetDllDirectory succeeded.");
            }

            string dllPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "smart_predictor_jni.dll");
            Console.WriteLine($"尝试加载 DLL: {dllPath}");

            Console.WriteLine("Welcome to Ronsson AI SDK");
            Console.WriteLine($"当前进程平台: {(Environment.Is64BitProcess ? "64位" : "32位")}");

            try
            {
                bool running = true;

                while (running)
                {
                    DisplayMenu();
                    char choice = Console.ReadKey(true).KeyChar;
                    Console.WriteLine();

                    switch (choice)
                    {
                        case 'a':
                            // SDK 授权
                            Console.WriteLine("SDK authorization...");
                            Console.Write("Enter authorization code: ");
                            string authCode = Console.ReadLine();

                            try
                            {
                                Console.WriteLine($"调用 SmartPredictor_sign: {MODEL_DIR}, {authCode}");
                                int code = SmartPredictor_sign(MODEL_DIR, authCode);
                                Console.WriteLine($"返回结果: {code}");

                                if (code == 0)
                                {
                                    Console.WriteLine("Authorization successful");
                                }
                                else
                                {
                                    Console.WriteLine($"Authorization failed with code: {code}");
                                }
                            }
                            catch (AccessViolationException ex)
                            {
                                Console.WriteLine($"访问冲突: {ex.Message}");
                            }
                            break;

                        case 'l':
                            // 加载模型
                            Console.WriteLine("Loading model...");
                            try
                            {
                                Console.WriteLine($"调用 SmartPredictor_load: {MODEL_DIR}, 4");
                                int result = SmartPredictor_load(MODEL_DIR, 4);
                                Console.WriteLine($"返回结果: {result}");

                                if (result < 0)
                                {
                                    Console.WriteLine("Failed to load model");
                                }
                                else
                                {
                                    Console.WriteLine("Model loaded successfully");
                                }
                            }
                            catch (AccessViolationException ex)
                            {
                                Console.WriteLine($"访问冲突: {ex.Message}");
                            }
                            break;

                        case 'p':
                            // 预测
                            Console.WriteLine("Processing image for prediction...");
                            try
                            {
                                byte[] imageData = ReadImage(TEST_IMAGE_PATH);
                                const int MAX_RESULT_SIZE = 1024; // 根据实际需求调整
                                byte[] buffer = new byte[MAX_RESULT_SIZE];
                                int resultCode = SmartPredictor_predict_img_filter(imageData, imageData.Length, PREDICTION_THRESHOLD, buffer, buffer.Length);
                                string predictResult = Encoding.UTF8.GetString(buffer).TrimEnd('\0');
                                Console.WriteLine($"Prediction resultCode: {resultCode}");
                                Console.WriteLine($"Prediction result: {predictResult}");
                            }
                            catch (Exception e)
                            {
                                Console.WriteLine($"Failed to predict image: {e.Message}");
                            }
                            break;

                        case 'r':
                            // 注册图像
                            Console.Write("Enter label for the image: ");
                            string label = Console.ReadLine();

                            try
                            {
                                byte[] imageData = ReadImage(TEST_IMAGE_PATH);
                                var start = DateTime.Now;

                                int registResult = SmartPredictor_regist_img(imageData, imageData.Length, label, 6);

                                var end = DateTime.Now;
                                var duration = (end - start).TotalMilliseconds;

                                Console.WriteLine($"Registration time: {duration}ms");
                                Console.WriteLine($"Registration result: {registResult}");
                            }
                            catch (Exception e)
                            {
                                Console.WriteLine($"Failed to register image: {e.Message}");
                            }
                            break;

                        case 's':
                            // 保存模型
                            Console.WriteLine("Saving model...");
                            if (SmartPredictor_save(MODEL_DIR) != 1)
                            {
                                Console.WriteLine("Failed to save model");
                            }
                            else
                            {
                                Console.WriteLine("Model saved successfully");
                            }
                            break;

                        case 'c':
                            // 清除模型
                            Console.WriteLine("Clearing model...");
                            if (SmartPredictor_reset(MODEL_DIR))
                            {
                                Console.WriteLine("Model cleared successfully");
                            }
                            else
                            {
                                Console.WriteLine("Failed to clear model");
                            }
                            break;

                        case 'd':
                            // 删除标签
                            Console.Write("Enter label to delete: ");
                            string labelToDelete = Console.ReadLine();

                            Console.WriteLine($"Deleting label '{labelToDelete}'...");
                            if (SmartPredictor_delete(labelToDelete))
                            {
                                Console.WriteLine("Label deleted successfully");
                            }
                            else
                            {
                                Console.WriteLine("Failed to delete label");
                            }
                            break;

                        case 'u':
                            // 卸载模型
                            Console.WriteLine("Unloading model...");
                            if (SmartPredictor_unload() == 0)
                            {
                                Console.WriteLine("Model unloaded successfully");
                            }
                            else
                            {
                                Console.WriteLine("Failed to unload model");
                            }
                            break;

                        case 'q':
                            // 退出
                            running = false;
                            break;

                        default:
                            Console.WriteLine("Invalid option. Please try again.");
                            break;
                    }

                    if (running)
                    {
                        Console.WriteLine();
                    }
                }
            }
            catch (DllNotFoundException ex)
            {
                Console.WriteLine($"Failed to load DLL: {ex.Message}");
            }
            catch (EntryPointNotFoundException ex)
            {
                Console.WriteLine($"Failed to find function: {ex.Message}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"An error occurred: {ex.Message}");
            }
            finally
            {
                Console.WriteLine("Press any key to exit...");
                Console.ReadKey();
            }
        }

        static void DisplayMenu()
        {
            Console.WriteLine("==== Ronsson AI SDK Tool ====");
            Console.WriteLine("Press 'a': SDK Authorization");
            Console.WriteLine("Press 'l': Load Model");
            Console.WriteLine("Press 'p': Predict Image (demo.jpg)");
            Console.WriteLine("Press 'r': Register Image (demo.jpg)");
            Console.WriteLine("Press 's': Save Model");
            Console.WriteLine("Press 'c': Clear Model");
            Console.WriteLine("Press 'd': Delete label from model");
            Console.WriteLine("Press 'u': Unload Model");
            Console.WriteLine("Press 'q': Quit");
            Console.WriteLine("===========================");
            Console.Write("Enter your choice: ");
        }

        static byte[] ReadImage(string filePath)
        {
            try
            {
                return File.ReadAllBytes(filePath);
            }
            catch (FileNotFoundException)
            {
                throw new Exception($"Failed to open image file: {filePath}");
            }
            catch (Exception ex)
            {
                throw new Exception($"Failed to read image file: {filePath} - {ex.Message}");
            }
        }
    }
}