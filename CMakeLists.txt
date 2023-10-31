cmake_minimum_required(VERSION 3.26)
project(katengine)


add_library(katengine
        src/kat/engine.cpp
        src/kat/engine.hpp
        src/kat/os/win32.cpp
        src/kat/os/win32.hpp
        src/kat/os/linux.cpp
        src/kat/os/linux.hpp)
target_compile_features(katengine PUBLIC cxx_std_20)

target_include_directories(katengine PUBLIC src/)

if (WIN32)
    set(KATLIBS)
elseif (UNIX)
    set(KATLIBS xcb)
else()
    message(FATAL_ERROR "Unsupported system")
endif()

target_link_libraries(katengine PUBLIC ${KATLIBS})

add_library(katengine::katengine ALIAS katengine)