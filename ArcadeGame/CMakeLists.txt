cmake_minimum_required(VERSION 3.0)
project(ArcadeGame)

add_subdirectory(fltk)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/fltk fltk)

add_executable(ArcadeGame WIN32 main.cpp)

target_link_libraries(ArcadeGame fltk)