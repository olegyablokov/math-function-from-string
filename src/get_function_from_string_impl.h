#pragma once
#include "../function_from_string_settings.h"

#include <functional>
#include <iostream>
#include <array>


class GetFunctionFromStringImpl
{
public:
    template<typename RET_TYPE, typename VAR_TYPE, size_t DIM>
    static std::function<RET_TYPE(std::array<VAR_TYPE, DIM>)> get_function_from_string(const std::string& str);

    static FunctionFromStringSettings Settings;

private:
    GetFunctionFromStringImpl() = delete;
};


template<typename RET_TYPE, typename VAR_TYPE, size_t DIM>
std::function<RET_TYPE(std::array<VAR_TYPE, DIM>)> GetFunctionFromStringImpl::get_function_from_string(const std::string& str)
{
    std::cout << str << std::endl;
    return std::function<RET_TYPE(std::array<VAR_TYPE, DIM>)>();
}

FunctionFromStringSettings GetFunctionFromStringImpl::Settings;
