cmake_minimum_required(VERSION 3.24)
project(NumericalMethods)

set(CMAKE_CXX_STANDARD 17)

add_executable(NumericalMethods main.cpp NumericalMethods.cpp NumericalMethods.h Logger.h Root.h Reader.h)
