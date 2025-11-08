cmake_minimum_required(VERSION 3.30)
project(Project_2b_draft)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project_2b_draft
    graph.cpp
    graph.h
    DataLoader.h
    DataLoader.cpp
    main.cpp)
