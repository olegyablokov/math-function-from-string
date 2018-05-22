## Getting started
This is a C++ library for creating a compiled (mathematical) function from a string. 

[![Build Status](https://travis-ci.org/oyyablokov/math-function-from-string.svg?branch=master)](https://travis-ci.org/oyyablokov/math-function-from-string)

## Usage
Let's say you want to have a compiled "sin(x0 + x1)" function. In order to achieve this, do the following:
1. Include this header into your C++ file:
```
 #include "path/to/this/project/get_function_from_string.h"
```
2. Initialize settings:
```
FunctionFromStringSettings settings { <some_params> };
```
3. Get your function by calling:
```
std::function fun = GetFunctionFromString::get_function_from_string<double, double, 2>("std::sin(arg[0] + arg[1])", settings);
```
Here the first template parameter is the function return type, the second is the arguments type and the third is the dimension. Note that `settings` is passed by non-const reference so that it will be changed (read in `function_from_string_settings.h` for more)  

After this you will be able to use the function by calling:
```
double var = fun(std::array<double, 2>{ 1.0, -4.5 });
```
