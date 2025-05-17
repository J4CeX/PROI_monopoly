cmake_minimum_required(VERSION 3.20...4.0)

project(BoardGame)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(boardgame main.cpp)
target_link_libraries(boardgame src_lib)