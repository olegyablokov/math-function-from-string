#pragma once

#include <array>
#include <functional>
#include <cmath>


#ifdef __cplusplus
extern "C" {
#endif

template<typename RET_TYPE, typename ARG_TYPE, size_t DIM>
__declspec(dllexport) RET_TYPE fun(const std::array<ARG_TYPE, DIM>& arg);

#ifdef __cplusplus
}
#endif