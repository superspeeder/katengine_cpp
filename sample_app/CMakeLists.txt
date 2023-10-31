cmake_minimum_required(VERSION 3.26)
project(katengine_sampleapp VERSION 0.1.0)

add_executable(sample_app src/app/main.cpp)
target_include_directories(sample_app src/)
target_link_libraries(sample_app katengine::katengine)