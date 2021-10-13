cmake_minimum_required(VERSION 3.11)

project(Cypher CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(../ImgLib ImgLibBuildDir)

add_executable(cypher main.cpp)

target_link_libraries(cypher ImgLib)

target_include_directories(cypher PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../ImgLib")