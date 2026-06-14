cmake_minimum_required(VERSION 3.10)
project(maintenanced)

set(CMAKE_CXX_STANDARD 17)

add_executable(maintenanced
        src/Display/DisplayController.cpp
        src/Display/DisplayController.h
        src/Display/HyprlandBackend.cpp
        src/Display/HyprlandBackend.h
        src/Display/DisplayBackend.h
        src/Display/KDEBackend.cpp
        src/Display/KDEBackend.h
        src/Display/SwayBackend.cpp
        src/Display/SwayBackend.h
        src/Display/KDEBackend.cpp
        src/Display/KDEBackend.h
        src/Display/X11Backend.cpp
        src/Display/X11Backend.h
        src/RGBLighting/RGBController.cpp
        src/RGBLighting/RGBController.h
)

target_include_directories(maintenanced PRIVATE include)

# OpenRGB CXX SDK
add_subdirectory(ThirdParty/OpenRGB-cppSDK)
target_link_libraries(maintenanced PRIVATE orgbsdk)