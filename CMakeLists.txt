cmake_minimum_required(VERSION 3.24)
project(NumericalMethods)

set(CMAKE_CXX_STANDARD 17)

add_executable(NumericalMethods main.cpp NumericalMethodsLab1.cpp NumericalMethods.h Logger.h Root.h Reader.h NumericalMethodsLab2.cpp labs/lab1.cpp labs/lab1.h labs/lab2.cpp labs/lab2.h labs/lab3.cpp labs/lab3.h NumericalMethodsLab3.cpp NumericalMethodsLab4.cpp labs/lab4.cpp labs/lab4.h)
