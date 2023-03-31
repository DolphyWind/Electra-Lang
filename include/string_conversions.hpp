#pragma once

#include <vector>
#include <string>
#include <direction.hpp>

namespace std
{
    std::string to_string(const Direction &direction);
    std::string to_string(const std::vector<Direction> &directions);
    std::string to_string(const std::string &str);
}