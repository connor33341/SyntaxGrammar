# Specify that this directory contains source files
add_library(OSCheckerLib os_detector.cpp software_checker.cpp)
target_include_directories(OSCheckerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# This will make sure that the headers are found correctly
target_link_libraries(OSCheckerLib tinyxml2::tinyxml2)
