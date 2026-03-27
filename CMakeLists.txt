cmake_minimum_required(VERSION 4.1)
project(DA_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DA_project
        src/main.cpp
        src/Input.cpp
        src/Parser.cpp
        src/Menu.cpp
        src/MaxFlow.cpp
)
