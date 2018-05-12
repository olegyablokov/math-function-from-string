#pragma once

#include <array>
#include <functional>
#include <cmath>


//template<typename RET_TYPE, typename ARG_TYPE, size_t DIM>
//RET_TYPE fun(const std::array<ARG_TYPE, DIM>& arg);

extern "C"
{
    double function(double x);
}