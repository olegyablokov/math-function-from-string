#pragma once

#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <stdexcept>


inline bool file_exist(const std::string& name)
{
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

inline std::string replace_substring(const std::string& str, const std::string& prev_substr, const std::string& new_substr)
{
    std::string return_str = str;
    if(prev_substr.empty()) return return_str;
    size_t start_pos = 0;
    while((start_pos = str.find(prev_substr, start_pos)) != std::string::npos)
    {
        return_str .replace(start_pos, prev_substr.length(), new_substr);
        start_pos += new_substr.length(); // In case 'new_substr' contains 'prev_substr', like replacing 'x' with 'yx'
    }
    return return_str;
}

inline void delete_file(const std::string& filename)
{
    if (!file_exist(filename)) return;
    if(std::remove(filename.c_str()) != 0)
    {
        throw(std::logic_error(std::string("Couldn't delete file ") + filename));
    }
}