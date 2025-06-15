cmake_minimum_required(VERSION 3.22)

option(USE_CCACHE "Enable using ccache" ON)
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM AND USE_CCACHE)
    message(STATUS "Using ccache: ${CCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

project(djinn)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# global compile options
add_compile_options(-Wall -Wextra -Wunused-result)

add_subdirectory(lib)
add_subdirectory(test)