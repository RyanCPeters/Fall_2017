cmake_minimum_required(VERSION 3.8)
project(IterMerge_assig4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        driver.cpp
        mergesort.cpp
        mergesortImproved.cpp
        mergesortImproved.h
        quicksort.cpp)

add_executable(IterMerge_assig4 ${SOURCE_FILES})