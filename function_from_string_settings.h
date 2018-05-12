#pragma once
#include <string>


struct FunctionFromStringSettings
{
    std::string command = "\"gcc -std=c++17 -shared -o libFunction.so -fPIC ";
    std::string function_source_filename = "function.cpp";
    std::string function_source_code = ""
        "#include <array>\n"
        "#include <functional>\n"
        "#include <cmath>\n"
        "\n"
        "extern RET_TYPE fun(const std::array<ARG_TYPE, DIM>& arg)\n"
        "{\n"
        "    return BODY;\n"
        "}";
    std::string RET_TYPE;           /**< Initialize it explicitly if compilation fails. */
    std::string ARG_TYPE;           /**< Initialize it explicitly if compilation fails. */
    std::string DIM;                /**< Initialize it explicitly if compilation fails. */
};
