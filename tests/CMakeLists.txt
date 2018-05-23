cmake_minimum_required(VERSION 3.8)
project(FunctionFromStringTest)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp temp.cpp simple_functions_tests.cpp cmath_functions_tests.cpp)
add_executable(FunctionFromStringTest ${SOURCE_FILES})
target_link_libraries(FunctionFromStringTest
        ${CMAKE_CURRENT_SOURCE_DIR}/../build/libFunctionFromString.a
        ${CMAKE_DL_LIBS})
