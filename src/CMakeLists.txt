file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS *.cpp)

add_library(richpp ${SRC_FILES})

target_include_directories(richpp PUBLIC ${PROJECT_SOURCE_DIR}/include)