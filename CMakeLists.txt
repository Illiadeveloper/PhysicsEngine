
cmake_minimum_required(VERSION 3.6)

project(Engine VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

add_subdirectory(external)

add_executable(Engine src/main.cpp)

target_link_libraries(Engine PUBLIC external_libs)

