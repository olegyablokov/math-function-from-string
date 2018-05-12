cmake_minimum_required(VERSION 3.8)
project(FunctionFromStringTest)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_PREFIX_PATH /opt/Qt)
#find_package(Qt5Widgets REQUIRED)

set(SOURCE_FILES main.cpp temp.cpp get_function_from_string_tests.cpp)
add_executable(FunctionFromStringTest ${SOURCE_FILES})
target_link_libraries(FunctionFromStringTest
        ${CMAKE_CURRENT_SOURCE_DIR}/../build/libFunctionFromString.a
        ${CMAKE_DL_LIBS})
