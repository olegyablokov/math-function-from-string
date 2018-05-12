#pragma once

#include <sys/stat.h>
#include <unistd.h>
#include <string>


inline bool file_exist(const std::string& name)
{
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

std::string replace_substring(const std::string& str, const std::string& prev_substr, const std::string& new_substr)
{
    std::string ret_str = str;
    size_t index = 0;
    while (true)
    {
        index = ret_str.find(prev_substr);
        if (index != std::string::npos) ret_str.replace(index, prev_substr.size(), new_substr);
        else break;
    }

    return ret_str;
}