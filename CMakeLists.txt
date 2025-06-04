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

include_directories(${PROJECT_SOURCE_DIR}/include)
add_compile_definitions(fieldsPath="${CMAKE_CURRENT_SOURCE_DIR}/data/fields.txt")
add_compile_definitions(eventCardsPath="${CMAKE_CURRENT_SOURCE_DIR}/data/eventCards.txt")
add_compile_definitions(savePath="${CMAKE_CURRENT_SOURCE_DIR}/saves/save.txt")

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(app)
