cmake_minimum_required(VERSION 3.17)
project(TemaSemnale)

set(CMAKE_CXX_STANDARD 11)

add_executable(TemaSemnale main.cpp Matrix.cpp Matrix.h activation_function.h exceptions.h exceptions.cpp MLP.cpp MLP.h)