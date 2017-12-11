cmake_minimum_required(VERSION 3.8)
project(msI_assig4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        driver.cpp
        mergesort.cpp
        mergesortImproved.hpp
        quicksort.cpp
        WorkDir.cpp
        WorkDir.hpp)

add_executable(msI_assig4 ${SOURCE_FILES})