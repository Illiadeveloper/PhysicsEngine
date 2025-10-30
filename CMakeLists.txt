cmake_minimum_required(VERSION 3.10)
project(Engine VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Engine ${SOURCES})

target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Engine PUBLIC external_libs)
