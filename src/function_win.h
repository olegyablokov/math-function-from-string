#pragma once

#include <array>
#include <functional>
#include <cmath>


#ifdef __cplusplus
extern "C" {
#endif

template<typename RET_TYPE, typename ARG_TYPE, size_t DIM>
__declspec(dllexport) RET_TYPE function(const std::array<ARG_TYPE, DIM>& arg);

#ifdef __cplusplus
}
#endif