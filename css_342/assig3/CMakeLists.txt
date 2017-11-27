cmake_minimum_required(VERSION 3.8)
project(assig3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        RCPeters_AnalysisGen.cpp
        RCPeters_AnalysisGen.h
        RCPeters_GCD.cpp
        RCPeters_GCD.h
        RCPeters_gcdDriver.cpp)

add_executable(assig3 ${SOURCE_FILES})