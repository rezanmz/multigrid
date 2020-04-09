cmake_minimum_required(VERSION 3.16)
project(multigrid)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(multigrid
        CRS.cpp
        h.h
        main.cpp
        MultigridSolver.cpp
        ReadMatrices.cpp
        Smoother.cpp)
