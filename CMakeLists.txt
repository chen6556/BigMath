cmake_minimum_required(VERSION 3.0.0)
project(BigMath VERSION 0.2.0)

enable_testing()
if (MSVC)
    # 设置 msvc 输入代码编码格式为 utf-8
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/)

include_directories(${PROJECT_SOURCE_DIR}/inc)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_executable(BigMath main.cpp ${_SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)