cmake_minimum_required(VERSION 3.10)
project(OSChecker)

set(CMAKE_CXX_STANDARD 11)

# Specify the directory where the source files are located
add_subdirectory(src)

# Find and include tinyxml2 library
find_package(tinyxml2 REQUIRED)

# Add executable and link tinyxml2
add_executable(OSChecker src/main.cpp src/os_detector.cpp src/software_checker.cpp)
target_link_libraries(OSChecker tinyxml2::tinyxml2)
