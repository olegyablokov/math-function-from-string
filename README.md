## Getting started
This is a C++ library for creating a compiled (mathematical) function from a string. 

## Usage
Let's say you want to have a compiled "sin(x0 + x1)" function. In order to achieve this, do the following:
1. Include this header into your c++ file:
```
 #include "path/to/this/project/get_function_from_string.h"
```
2. Initialize settings:
```
GetFunctionFromString::set_settings(FunctionFromStringSettings(<some_params>));
```
3. Get your function by calling:
```
std::function fun = GetFunctionFromString::get_function_from_string<double, double, 2>("std::sin(arg[0] + arg[1])");
```
Here the first template parameter is the function return type, the second is the arguments type and the third is the dimension.
After this you will be able to use the function by calling:
```
double var = fun(std::array<double, 2>{ 1.0, -4.5 });
```
