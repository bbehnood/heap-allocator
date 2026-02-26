cmake_minimum_required(VERSION 3.16)
project(heap_allocator C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(heap_allocator
    src/allocator.c
)

target_include_directories(heap_allocator
    PUBLIC include
    PRIVATE src
)

add_executable(test_allocator test/main.c)
target_link_libraries(test_allocator heap_allocator)
