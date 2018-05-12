#pragma once
#include <functional>


template<typename RET_TYPE, typename VAR_TYPE, size_t DIM>
std::function<RET_TYPE(std::array<VAR_TYPE, DIM>)> get_function_from_string(const std::string& str);
