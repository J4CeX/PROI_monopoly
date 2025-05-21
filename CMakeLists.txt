cmake_minimum_required(VERSION 3.20)

project(BoardGame VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_C_COMPILER "/usr/bin/clang")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
include_directories(${PROJECT_SOURCE_DIR}/include)
qt_standard_project_setup()

add_subdirectory(src/app)
