cmake_minimum_required(VERSION 3.27)
project(pr1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(pr1
        Simulation.cpp
        Simulation.h
        Renderer.h
        Renderer.cpp
        main.cpp)
