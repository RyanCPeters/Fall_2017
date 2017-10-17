cmake_minimum_required(VERSION 3.8)
project(css_342)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
#        assig1/complex.h
#        assig1/RyanP_test_case_complexDriver.cpp
#        assig1/complex.h assig1/complex.cpp
        assig2/cannibals.h
        assig2/cannibals.cpp
        assig2/main.cpp)

add_executable(css_342 ${SOURCE_FILES} )