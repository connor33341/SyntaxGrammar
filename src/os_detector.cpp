#include "os_detector.hpp"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#elif defined(__linux__) || defined(__unix__)
    #include <unistd.h>
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
#endif

std::string OSDetector::detectOS() {
#if defined(_WIN32) || defined(_WIN64)
    return "Windows";
#elif defined(__APPLE__) || defined(__MACH__)
    #if TARGET_IPHONE_SIMULATOR == 1
        return "iOS Simulator";
    #elif TARGET_OS_IPHONE == 1
        return "iOS";
    #elif TARGET_OS_MAC == 1
        return "macOS";
    #else
        return "Unknown Apple OS";
    #endif
#elif defined(__linux__)
    return "Linux";
#elif defined(__unix__)
    return "Unix";
#else
    return "Unknown OS";
#endif
}
