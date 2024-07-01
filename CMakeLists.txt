cmake_minimum_required(VERSION 3.25)
project(PF_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PF_Project
        header.h
        original.cpp)
