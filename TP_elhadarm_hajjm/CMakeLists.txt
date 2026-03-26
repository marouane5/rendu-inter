cmake_minimum_required(VERSION 3.16)
project(cppma_tps CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

enable_testing()

add_subdirectory(tp1)
add_subdirectory(tp2)
add_subdirectory(tp3)
add_subdirectory(tp4)
