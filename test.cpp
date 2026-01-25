#include <iostream>
#include <vector>
#include <string>

int main() {
    std::cout << "Hello from C++!" << std::endl;
    std::cout << "C++ version: __cplusplus =  " << __cplusplus << std::endl;
    std::cout << "if MSVC version: _MSVC_LANG =  "<< _MSVC_LANG << std::endl;

    // 使用一些现代C++特性
    std::vector<std::string> messages = {
        "This is a C++17 program",
        "Compiled with TDM-GCC",
        "Running in temp directory"
    };
    
    for (const auto& msg : messages) {
        std::cout << "- " << msg << std::endl;
    }
    
    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    return 0;
}