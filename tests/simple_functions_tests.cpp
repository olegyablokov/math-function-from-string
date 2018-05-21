#include "catch.hpp"
#include "../get_function_from_string.h"
#include "../src/utility.h"
#include <string>


TEST_CASE("Function works with simple 1-dim expression", "[get-function-from-string]" )
{
    FunctionFromStringSettings settings;
    settings.RET_TYPE = "double";
    settings.ARG_TYPE = "double";
    settings.DIM = "1";
    GetFunctionFromString::set_settings(settings);

    std::string function_str = "2 * arg[0]";
    auto function = GetFunctionFromString::get_function_from_string<double, double, 1>(function_str);

    REQUIRE(function(std::array<double, 1>{0}) == Approx(0));
    REQUIRE(function(std::array<double, 1>{1}) == Approx(2));
    REQUIRE(function(std::array<double, 1>{2}) == Approx(4));
    REQUIRE(function(std::array<double, 1>{-1}) == Approx(-2));
    REQUIRE(function(std::array<double, 1>{1.4}) == Approx(2.8));
}

TEST_CASE("Function works with simple N-dim expression", "[get-function-from-string]" )
{
    FunctionFromStringSettings settings;
    settings.RET_TYPE = "double";
    settings.ARG_TYPE = "double";
    settings.DIM = "3";
    GetFunctionFromString::set_settings(settings);

    std::string function_str = "arg[0] + arg[1] + arg[2]";
    auto function = GetFunctionFromString::get_function_from_string<double, double, 3>(function_str);

    REQUIRE(function(std::array<double, 3>{0, 0, 0}) == Approx(0));
    REQUIRE(function(std::array<double, 3>{1, 1, 2}) == Approx(4));
    REQUIRE(function(std::array<double, 3>{2, -1.9, 1000}) == Approx(1000.1));
}

TEST_CASE("Files created with proper names and deleted", "[get-function-from-string]" )
{
    FunctionFromStringSettings settings;
    settings.RET_TYPE = "double";
    settings.ARG_TYPE = "double";
    settings.function_source_filename = "test_function.cpp";
    settings.DIM = "1";
    GetFunctionFromString::set_settings(settings);

    std::string function_str = "arg[0] + arg[1] + arg[2]";
    auto function = GetFunctionFromString::get_function_from_string<double, double, 3>(function_str);

    REQUIRE(!file_exist("test_function.cpp"));
}