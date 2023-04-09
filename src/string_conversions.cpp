/**
MIT License

Copyright (c) 2023 Yunus Emre Aydın

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <string_conversions.hpp>


std::string std::to_string(const Direction &direction)
{
    switch (direction)
    {
    case Direction::EAST:
        return "east";
        break;
    case Direction::NORTHEAST:
        return "northeast";
        break;
    case Direction::NORTH:
        return "north";
        break;
    case Direction::NORTHWEST:
        return "northwest";
        break;
    case Direction::WEST:
        return "west";
        break;
    case Direction::SOUTHWEST:
        return "southwest";
        break;
    case Direction::SOUTH:
        return "south";
        break;
    case Direction::SOUTHEAST:
        return "southeast";
        break;
    case Direction::NONE:
    default:
        return "none";
        break;
    }
}

std::wstring std::to_wstring(const Direction &direction)
{
    switch (direction)
    {
    case Direction::EAST:
        return L"east";
        break;
    case Direction::NORTHEAST:
        return L"northeast";
        break;
    case Direction::NORTH:
        return L"north";
        break;
    case Direction::NORTHWEST:
        return L"northwest";
        break;
    case Direction::WEST:
        return L"west";
        break;
    case Direction::SOUTHWEST:
        return L"southwest";
        break;
    case Direction::SOUTH:
        return L"south";
        break;
    case Direction::SOUTHEAST:
        return L"southeast";
        break;
    case Direction::NONE:
    default:
        return L"none";
        break;
    }
}

std::string std::to_string(const std::vector<Direction> &directions)
{
    std::string result = "{";
    for(std::size_t i = 0; i < directions.size(); i++)
    {
        result += std::to_string(directions[i]);
        if(i == directions.size() - 1) result += ", ";
    }
    result += "}";
    return result;
}

std::wstring std::to_wstring(const std::vector<Direction> &directions)
{
    std::wstring result = L"{";
    for(std::size_t i = 0; i < directions.size(); i++)
    {
        result += std::to_wstring(directions[i]);
        if(i == directions.size() - 1) result += L", ";
    }
    result += L"}";
    return result;
}

std::string std::to_string(const std::string &str)
{
    return str;
}

std::wstring std::to_wstring(const std::wstring &str)
{
    return str;
}

std::wstring std::to_wstring(const std::string &str)
{
    return std::wstring(str.begin(), str.end());
}