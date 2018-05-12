#pragma once
#include "../function_from_string_settings.h"
#include "utility.h"

#include <functional>
#include <iostream>
#include <fstream>
#include <array>

#ifdef __linux__
#include <dlfcn.h>
#endif

class GetFunctionFromStringImpl
{
public:
    GetFunctionFromStringImpl() = delete;

    template<typename RET_TYPE, typename ARG_TYPE, size_t DIM>
    static std::function<RET_TYPE(std::array<ARG_TYPE, DIM>)> get_function_from_string(const std::string& str);

    static void set_settings(const FunctionFromStringSettings& settings);
    static FunctionFromStringSettings get_settings();

private:
    template<typename RET_TYPE, typename ARG_TYPE, size_t DIM>
    static void create_source_file(const std::string& body);

    static FunctionFromStringSettings Settings;
};


void GetFunctionFromStringImpl::set_settings(const FunctionFromStringSettings& settings)
{
    GetFunctionFromStringImpl::Settings = settings;
}

FunctionFromStringSettings GetFunctionFromStringImpl::get_settings()
{
    return GetFunctionFromStringImpl::Settings;
}

template<typename RET_TYPE, typename ARG_TYPE, size_t DIM>
void GetFunctionFromStringImpl::create_source_file(const std::string& body)
{
    std::string source_code = Settings.function_source_code;

    std::string name_ret_type = Settings.RET_TYPE.empty() ? typeid(RET_TYPE).name() : Settings.RET_TYPE;
    std::string name_val_type = Settings.ARG_TYPE.empty() ? typeid(ARG_TYPE).name() : Settings.ARG_TYPE;
    std::string name_dim = Settings.DIM.empty() ? typeid(DIM).name() : Settings.DIM;

    source_code = replace_substring(source_code, "RET_TYPE", name_ret_type);
    source_code = replace_substring(source_code, "ARG_TYPE", name_val_type);
    source_code = replace_substring(source_code, "DIM", name_dim);
    source_code = replace_substring(source_code, "BODY", body);

    std::ofstream file;
    file.open(Settings.function_source_filename);
    file << source_code;
    file.close();
};

template<typename RET_TYPE, typename ARG_TYPE, size_t DIM>
std::function<RET_TYPE(std::array<ARG_TYPE, DIM>)> GetFunctionFromStringImpl::get_function_from_string(const std::string& str)
{
    std::function<RET_TYPE(std::array<ARG_TYPE, DIM>)> function;

    create_source_file(str);
    system((Settings.command + " " + Settings.function_source_filename).c_str());

#ifdef _WIN32

#elif __linux__
    void *handle;
    char *error;
    handle = dlopen ("/home/oleg/MyProjects/FunctionFromString/tests/build/libFunction.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();    /* Clear any existing error */
    auto function_from_so =  (double(*)(double)) dlsym(handle, "_Z3fund");
    if ((error = dlerror()) != NULL)
    {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    dlclose(handle);
    function = std::function<RET_TYPE(std::array<ARG_TYPE, DIM>)>(&function_from_so);
//    function  = static_cast<std::function<RET_TYPE(std::array<ARG_TYPE, DIM>)>>(*function_from_so);
#endif

    return function;
}

FunctionFromStringSettings GetFunctionFromStringImpl::Settings;
