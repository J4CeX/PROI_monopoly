cmake_minimum_required(VERSION 3.20)

project(BoardGame VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
# set(CMAKE_C_COMPILER "/usr/bin/clang")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
include_directories(${PROJECT_SOURCE_DIR}/include)
qt_standard_project_setup()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/include)
add_compile_definitions(fieldsPath="${CMAKE_CURRENT_SOURCE_DIR}/data/fields.txt")
add_compile_definitions(eventCardsPath="${CMAKE_CURRENT_SOURCE_DIR}/data/eventCards.txt")

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(app)