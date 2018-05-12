#include "get_function_from_string.h"
#include <iostream>

//
//template<typename RET_TYPE, typename Args ...>
//void get_function_from_string(const std::string& str, std::function<RET_TYPE(Args...)>)
//{
//    std::cout << "dads" << std::endl;
//};

template<typename RET_TYPE, typename VAR_TYPE, size_t DIM>
std::function<RET_TYPE(std::array<VAR_TYPE, DIM>)> get_function_from_string(const std::string& str)
{
    std::cout << str << std::endl;
}
