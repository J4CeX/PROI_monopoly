add_executable(game_gui main.cpp)

target_link_libraries(game_gui PRIVATE richpp)

target_include_directories(game_gui PRIVATE ${PROJECT_SOURCE_DIR}/include)
