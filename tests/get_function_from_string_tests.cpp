#include "catch.hpp"
#include "../get_function_from_string.h"

#include <string>


TEST_CASE("Function works on Windows", "[windows-end-to-end]" )
{
    FunctionFromStringSettings settings;
    settings.RET_TYPE = "double";
    settings.ARG_TYPE = "double";
    settings.DIM = "1";
    GetFunctionFromString::set_settings(settings);

    std::string function_str = "2 * arg[0]";
    auto function = GetFunctionFromString::get_function_from_string<double, double, 1>(function_str);

    REQUIRE(function(std::array<double, 1>{0}) == 0);
    REQUIRE(function(std::array<double, 1>{1}) == 1);
    REQUIRE(function(std::array<double, 1>{2}) == 4);
    REQUIRE(function(std::array<double, 1>{-1}) == -2);
    REQUIRE(function(std::array<double, 1>{1.4}) == 2.8);
}
