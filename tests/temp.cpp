//#include "../get_function_from_string.h"
//#include "function.h"
//
//#include <iostream>
//#include <fstream>
//#include <cstdarg>
//#include <array>
//#include <cmath>
//#include <vector>
//
//#include <sys/stat.h>
//#include <unistd.h>
//
//#include <dlfcn.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//
//inline bool file_exist(const std::string& name)
//{
//    struct stat buffer;
//    return (stat (name.c_str(), &buffer) == 0);
//}
//
//double norm(std::array<double, 3> x)
//{
//    return std::sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
//}
//
//template<typename RET_TYPE, typename VAR_TYPE, size_t DIM>
//std::function<RET_TYPE(std::array<VAR_TYPE, DIM>)> get(const std::string& str)
//{
////    auto g = @RET_TYPE;
//    std::cout << "get() called" << std::endl;
//    return std::function<RET_TYPE(std::array<VAR_TYPE, DIM>)>(norm);
//};
//
//int main()
//{
//    std::string filename = "function.cpp";
//    if (!file_exist(filename))
//    {
//        std::ofstream file;
//        file.open(filename);
//        file << "#include <array>\n"
//            "#include <functional>\n"
//            "#include <cmath>\n"
//            "\n"
//            "extern double fun(double arg)\n"
//            "{\n"
//            "    return arg * arg;\n"
//            "}";
//        file.close();
//        system((std::string("gcc -std=c++17 -shared -o libFunction.so -fPIC ") + filename).c_str());
//    }
//
//    void *handle;
//    char *error;
//    handle = dlopen ("/home/oleg/MyProjects/FunctionFromString/tests/build/libFunction.so", RTLD_LAZY);
//    if (!handle)
//    {
//        fprintf (stderr, "%s\n", dlerror());
//        exit(1);
//    }
//    dlerror();    /* Clear any existing error */
//    auto function_from_so =  (double(*)(double)) dlsym(handle, "_Z3fund");
//    if ((error = dlerror()) != NULL)  {
//        fprintf (stderr, "%s\n", error);
//        exit(1);
//    }
//    printf ("%f\n", function_from_so(2.0));
//    dlclose(handle);
//
////    auto f1 = static_cast<double(double)>(*function_from_so);
////    std::cout << f1(42) << std::endl;
//
//    std::cout << "TEST WORKS" << std::endl;
////    auto function = std::function<double(int)>(&fun);
////    auto f1 = get<double, double, 3>();
////    std::cout << f1(std::array<double, 3>{1, 2, 3}) << std::endl;
//
//    return 0;
//}
