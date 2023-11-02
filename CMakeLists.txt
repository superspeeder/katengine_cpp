cmake_minimum_required(VERSION 3.26)
project(katengine)

find_package(glm CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

add_library(katengine
        src/kat/engine.cpp
        src/kat/engine.hpp
        src/kat/os/window.cpp
        src/kat/os/window.hpp)

target_compile_features(katengine PUBLIC cxx_std_20)

target_include_directories(katengine PUBLIC src/)

target_link_libraries(katengine PUBLIC ${KATLIBS} glm::glm Vulkan::Vulkan)

add_library(katengine::katengine ALIAS katengine)