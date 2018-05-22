#include "catch.hpp"
#include "../get_function_from_string.h"

#include <string>


TEST_CASE("Function works with cmath functions", "[cmath]" )
{
    FunctionFromStringSettings settings;
    settings.RET_TYPE = "double";
    settings.ARG_TYPE = "double";
    settings.DIM = "1";

    auto function_sin = GetFunctionFromString::get_function_from_string<double, double, 1>("std::sin(arg[0])", settings);
    CHECK(function_sin(std::array<double, 1>{0}) == Approx(0));
    CHECK(function_sin(std::array<double, 1>{M_PI / 2}) == Approx(1));
    CHECK(function_sin(std::array<double, 1>{M_PI}) == Approx(0));

    // clear the working directory
    if (file_exist(settings.lib_filename)) system((std::string("rm ") + settings.lib_filename).c_str());
    if (file_exist(settings.function_source_filename)) system((std::string("rm ") + settings.function_source_filename).c_str());
}