cmake_minimum_required(VERSION 3.22.0)
project(BigMath VERSION 0.2.0)

if (MSVC)
    add_compile_options("/utf-8")
    add_compile_options("/arch:AVX2")
    add_compile_options("/MP")
elseif (CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options("-m64")
    add_compile_options("-mavx2")
    add_compile_options("-funroll-loops")
    add_compile_options("-ffunction-sections")
    add_compile_options("-fdata-sections")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/)

include_directories(${PROJECT_SOURCE_DIR}/inc)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_executable(BigMath main.cpp ${_SOURCES})