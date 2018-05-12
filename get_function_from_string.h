#pragma once
#include "src/get_function_from_string_impl.h"
#include "function_from_string_settings.h"

#include <functional>
#include <iostream>
#include <array>


class GetFunctionFromString
{
public:
    GetFunctionFromString() = delete;

    template<typename RET_TYPE, typename VAR_TYPE, size_t DIM>
    static std::function<RET_TYPE(std::array<VAR_TYPE, DIM>)> get_function_from_string(const std::string& str);

    static void set_settings(const FunctionFromStringSettings& settings);
    static FunctionFromStringSettings get_settings();
};





void GetFunctionFromString::set_settings(const FunctionFromStringSettings& settings)
{
    GetFunctionFromStringImpl::set_settings(settings);
}

FunctionFromStringSettings GetFunctionFromString::get_settings()
{
    return GetFunctionFromStringImpl::get_settings();
}

template<typename RET_TYPE, typename VAR_TYPE, size_t DIM>
std::function<RET_TYPE(std::array<VAR_TYPE, DIM>)> GetFunctionFromString::get_function_from_string(const std::string& str)
{
    return GetFunctionFromStringImpl::get_function_from_string<RET_TYPE, VAR_TYPE, DIM>(str);
}
