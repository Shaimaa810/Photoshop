cmake_minimum_required(VERSION 3.24)
project(Photoshop)

set(CMAKE_CXX_STANDARD 17)

add_executable(Photoshop main.cpp)
add_executable(GrayImage GrayImage.cpp ColoredImage.cpp)
add_executable(ColoredImage ColoredImage.cpp)