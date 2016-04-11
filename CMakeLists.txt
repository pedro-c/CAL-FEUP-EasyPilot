cmake_minimum_required(VERSION 3.5)
project(CAL_FEUP_EasyPilot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/Coordinates.cpp
    src/Coordinates.h
    src/Edge.h
    src/Graph.h
    src/Intersection.cpp
    src/Intersection.h
    src/main.cpp
    src/Road.cpp
    src/Road.h
    src/Vertex.h)

add_executable(CAL_FEUP_EasyPilot ${SOURCE_FILES})