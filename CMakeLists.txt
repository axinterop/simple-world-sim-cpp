cmake_minimum_required(VERSION 3.27)
project(pr1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(pr1
        Simulation.cpp
        Simulation.h
        Renderer.h
        Renderer.cpp
        main.cpp
        Organism.h
        util.h
        Organism.cpp
        Animal.h
        Animal.cpp
        World.h
        World.cpp
        WorldListener.h
        WorldListener.cpp
        animals/Wolf.h
        animals/Wolf.cpp
        animals/Sheep.h
        animals/Sheep.cpp
        animals/Fox.h
        animals/Fox.cpp
        animals/Turtle.h
        animals/Turtle.cpp
        animals/Antilope.h
        animals/Antilope.cpp
        animals/Human.h
        animals/Human.cpp)
