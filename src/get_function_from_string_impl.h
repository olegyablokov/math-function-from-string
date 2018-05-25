#pragma once

#include "../function_from_string_settings.h"
#include "utility.h"
#include <functional>
#include <iostream>
#include <fstream>
#include <array>

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <dlfcn.h>
#endif


class GetFunctionFromStringImpl
{
public:
    GetFunctionFromStringImpl() = delete;

    template<typename RET_TYPE, typename ARG_TYPE, size_t DIM>
    static std::function<RET_TYPE(const std::array<ARG_TYPE, DIM>&)> get_function_from_string(const std::string& str,
                                                                                              FunctionFromStringSettings& settings);

private:
    template<typename RET_TYPE, typename ARG_TYPE, size_t DIM>
    static std::string create_source_file(const std::string& body, const FunctionFromStringSettings& settings);
    static int n;
};


template<typename RET_TYPE, typename ARG_TYPE, size_t DIM>
std::string GetFunctionFromStringImpl::create_source_file(const std::string& body, const FunctionFromStringSettings& settings)
{
    std::string source_code = settings.function_source_code;

    std::string name_ret_type = settings.RET_TYPE.empty() ? typeid(RET_TYPE).name() : settings.RET_TYPE;
    std::string name_val_type = settings.ARG_TYPE.empty() ? typeid(ARG_TYPE).name() : settings.ARG_TYPE;
    std::string name_dim = settings.DIM.empty() ? typeid(DIM).name() : settings.DIM;

    source_code = replace_substring(source_code, "RET_TYPE", name_ret_type);
    source_code = replace_substring(source_code, "ARG_TYPE", name_val_type);
    source_code = replace_substring(source_code, "DIM", name_dim);
    source_code = replace_substring(source_code, "BODY", body);
    source_code = replace_substring(source_code, "FUNCTION_NAME", settings.function_name);

    std::ofstream file;
    file.open(settings.function_source_filename);
    file << source_code;
    file.close();
    return source_code;
};

template<typename RET_TYPE, typename ARG_TYPE, size_t DIM>
std::function<RET_TYPE(const std::array<ARG_TYPE, DIM>&)> GetFunctionFromStringImpl::get_function_from_string(const std::string& str,
                                                                                                              FunctionFromStringSettings& settings)
{
    using func_ptr = RET_TYPE (*)(const std::array<ARG_TYPE, DIM>&);
    std::function<RET_TYPE(const std::array<ARG_TYPE, DIM>&)> function;

    // create lib_filename:
    std::string lib_filename = settings.lib_filename;
    std::string temp = replace_substring(lib_filename, ".", std::to_string(n) + ".");
    while(file_exist(temp))
    {
        ++n;
        temp = replace_substring(lib_filename, ".", std::to_string(n) + ".");
    }
    lib_filename = temp;
    settings.lib_filename = temp;

    // create function_name:
    settings.function_name += std::to_string(n);

    settings.function_source_code = create_source_file<RET_TYPE, ARG_TYPE, DIM>(str, settings);

    // create command:
    std::string command = settings.command;
    command = replace_substring(command, "<function_source_filename>", settings.function_source_filename);
    command = replace_substring(command, "<lib_filename>", lib_filename);

    // execute command:
    system(command.c_str());

#ifdef _WIN32
    HINSTANCE h_function_DLL = LoadLibrary(settings.lib_filename.c_str());
    if (!h_function_DLL )
    {
        DWORD error = GetLastError();
        throw(std::logic_error("Couldn't load library. Error code: " + error));
    }

    auto function_ptr = reinterpret_cast<func_ptr>(GetProcAddress(GetModuleHandle(TEXT(settings.lib_filename.c_str())), settings.function_name.c_str()));
    if (!function_ptr)
    {
        DWORD error = GetLastError();
        throw(std::logic_error("Couldn't load function from library. Error code: " + error));
    }
    function = function_ptr;

#elif __linux__
    void *handle;
    char *error;

    handle = dlopen(std::string("./" + lib_filename).c_str(), RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "%s\n", dlerror());
        throw(EXIT_FAILURE);
        //TODO: catch this properly
    }

    dlerror();

    auto function_from_so = reinterpret_cast<func_ptr>(dlsym(handle, settings.function_name.c_str()));

    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "%s\n", error);
        throw(EXIT_FAILURE);
        //TODO: catch this properly
    }

    function = function_from_so;
    settings.handle = handle;

//    dlclose(handle);
#endif

    delete_file(settings.function_source_filename);
    ++n;

    return function;
}
