//#include "catch.hpp"
//#include "../get_function_from_string.h"
//
//#include <string>
//
//
//TEST_CASE("Function works with cmath functions", "[cmath]" )
//{
////    FunctionFromStringSettings settings;
////    settings.RET_TYPE = "double";
////    settings.ARG_TYPE = "double";
////    settings.DIM = "1";
////    GetFunctionFromString::set_settings(settings);
//
////    auto function_sin = GetFunctionFromString::get_function_from_string<double, double, 1>("std::sin(arg[0])");
////    REQUIRE(function_sin(std::array<double, 1>{0}) == Approx(0));
////    REQUIRE(function_sin(std::array<double, 1>{M_PI / 2}) == Approx(1));
////    REQUIRE(function_sin(std::array<double, 1>{M_PI}) == Approx(0));
//}