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
    static std::function<RET_TYPE(const std::array<ARG_TYPE, DIM>&)> get_function_from_string(const std::string& str,
                                                                                              FunctionFromStringSettings& settings);

private:
    template<typename RET_TYPE, typename ARG_TYPE, size_t DIM>
    static void create_source_file(const std::string& body, FunctionFromStringSettings& settings);
};


template<typename RET_TYPE, typename ARG_TYPE, size_t DIM>
void GetFunctionFromStringImpl::create_source_file(const std::string& body, FunctionFromStringSettings& settings)
{
    std::string source_code = settings.function_source_code;

    std::string name_ret_type = settings.RET_TYPE.empty() ? typeid(RET_TYPE).name() : settings.RET_TYPE;
    std::string name_val_type = settings.ARG_TYPE.empty() ? typeid(ARG_TYPE).name() : settings.ARG_TYPE;
    std::string name_dim = settings.DIM.empty() ? typeid(DIM).name() : settings.DIM;

    source_code = replace_substring(source_code, "RET_TYPE", name_ret_type);
    source_code = replace_substring(source_code, "ARG_TYPE", name_val_type);
    source_code = replace_substring(source_code, "DIM", name_dim);
    source_code = replace_substring(source_code, "BODY", body);

    std::ofstream file;
    file.open(settings.function_source_filename);
    file << source_code;
    file.close();
};

template<typename RET_TYPE, typename ARG_TYPE, size_t DIM>
std::function<RET_TYPE(const std::array<ARG_TYPE, DIM>&)> GetFunctionFromStringImpl::get_function_from_string(const std::string& str,
                                                                                                              FunctionFromStringSettings& settings)
{
    std::function<RET_TYPE(const std::array<ARG_TYPE, DIM>&)> function;

    create_source_file<RET_TYPE, ARG_TYPE, DIM>(str, settings);

    // create lib_filename:
    std::string lib_filename = settings.lib_filename;
    int n = 0;
    std::string temp = lib_filename;
    while(file_exist(temp))
    {
        ++n;
        temp = replace_substring(lib_filename, ".", std::to_string(n) + ".");
    }
    lib_filename = temp;
    settings.lib_filename = temp;

    // create command:
    std::string command = settings.command;
    command = replace_substring(command, "<function_source_filename>", settings.function_source_filename);
    command = replace_substring(command, "<lib_filename>", lib_filename);

    // execute command:
    system(command.c_str());

#ifdef _WIN32
    //TODO: implement this
    throw("Not implemented for windows");

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

    using func_ptr = RET_TYPE (*)(const std::array<ARG_TYPE, DIM>&);
    auto function_from_so = reinterpret_cast<func_ptr>(dlsym(handle, "function"));

    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "%s\n", error);
        throw(EXIT_FAILURE);
        //TODO: catch this properly
    }

    function = function_from_so;

//    dlclose(handle);
#endif

    // delete file:
    if(std::remove(settings.function_source_filename.c_str()) != 0 )
    {
        //TODO: catch this properly
        throw(std::string("Couldn't delete file") + settings.function_source_filename);
    }
    return function;
}
