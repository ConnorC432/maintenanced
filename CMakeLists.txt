cmake_minimum_required(VERSION 3.20)
project(maintenanced)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-fcoroutines)

# Source Files
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
        src/Display/X11Backend.cpp
        src/Display/X11Backend.h
        src/RGBLighting/RGBController.cpp
        src/RGBLighting/RGBController.h
        src/Packages/PackageManagerController.cpp
        src/Packages/PackageManagerController.h
        src/Packages/PackageBackend.h
        src/Packages/PacmanBackend.cpp
        src/Packages/PacmanBackend.h
        src/Packages/AptBackend.cpp
        src/Packages/AptBackend.h
)

target_include_directories(maintenanced PRIVATE include)

# OpenRGB CXX SDK
add_subdirectory(ThirdParty/OpenRGB-cppSDK)
target_link_libraries(maintenanced PRIVATE orgbsdk)

# sdbus c++
add_subdirectory(ThirdParty/sdbus-cpp)
target_link_libraries(maintenanced PRIVATE SDBusCpp::sdbus-c++)