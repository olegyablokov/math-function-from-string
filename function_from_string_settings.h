#pragma once
#include <string>


struct FunctionFromStringSettings
{
    std::string command;
    std::string function_source_filename;
    std::string function_header;
    std::string function_source_code;
    std::string RET_TYPE;           /**< Initialize it explicitly if compilation fails. */
    std::string ARG_TYPE;           /**< Initialize it explicitly if compilation fails. */
    std::string DIM;                /**< Initialize it explicitly if compilation fails. */

    FunctionFromStringSettings()
    {
        function_source_filename = "function.cpp";

#ifdef _WIN32
        function_source_code = ""
            "#include <array>\n"
            "#include <functional>\n"
            "#include <cmath>\n"
            "\n"
            "extern RET_TYPE fun(const std::array<ARG_TYPE, DIM>& arg)\n"
            "{\n"
            "    return BODY;\n"
            "}";
        command = "\"gcc -std=c++17 -shared -o libFunction.so -fPIC ";
        function_header = "function_linux.h";

#elif __linux__
        function_source_code = ""
            "#include <array>\n"
            "#include <functional>\n"
            "#include <cmath>\n"
            "\n"
            "extern RET_TYPE fun(const std::array<ARG_TYPE, DIM>& arg)\n"
            "{\n"
            "    return BODY;\n"
            "}"
        command = "\"gcc -std=c++17 -shared -o libFunction.so -fPIC ";
        function_header = "function_win.h";
#endif
    }
};
