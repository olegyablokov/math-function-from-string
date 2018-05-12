cmake_minimum_required(VERSION 3.8)
project(FunctionFromString)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        function_from_string_settings.h
        get_function_from_string.h
        src/get_function_from_string_impl.cpp
        src/get_function_from_string_impl.h
        src/utility.h)
add_library(FunctionFromString ${SOURCE_FILES})