cmake_minimum_required(VERSION 3.8)
project(FunctionFromString)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES get_function_from_string.cpp get_function_from_string.h)
add_library(FunctionFromString ${SOURCE_FILES})