set(SOURCES
    Field.cpp
)

add_library(src_lib STATIC ${SOURCES})
target_include_directories(src_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)