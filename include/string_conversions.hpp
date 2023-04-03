#pragma once

#include <vector>
#include <string>
#include <direction.hpp>

namespace std
{
    std::string to_string(const Direction &direction);
    std::string to_string(const std::vector<Direction> &directions);
    std::string to_string(const std::string &str);

    std::wstring to_wstring(const Direction &direction);
    std::wstring to_wstring(const std::vector<Direction> &directions);
    std::wstring to_wstring(const std::wstring &str);
    std::wstring to_wstring(const std::string &str);
}