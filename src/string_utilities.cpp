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

#include <string_utilities.hpp>

namespace sutil
{

    std::string to_string(const Direction& direction)
    {
        switch (direction)
        {
            case Direction::EAST:
                return "east";
            case Direction::NORTHEAST:
                return "northeast";
            case Direction::NORTH:
                return "north";
            case Direction::NORTHWEST:
                return "northwest";
            case Direction::WEST:
                return "west";
            case Direction::SOUTHWEST:
                return "southwest";
            case Direction::SOUTH:
                return "south";
            case Direction::SOUTHEAST:
                return "southeast";
            case Direction::NONE:
            default:
                return "none";
        }
    }

    std::string to_string(const std::vector<Direction>& directions)
    {
        std::string result = "{";
        for(std::size_t i = 0; i < directions.size(); i++)
        {
            result += sutil::to_string(directions[i]);
            if(i != directions.size() - 1) result += ", ";
        }
        result += "}";
        return result;
    }

    std::string to_string(const std::string& str)
    {
        return str;
    }

    std::string to_string(const std::u32string& str)
    {
        std::string out;
        utf8::utf32to8(str.begin(), str.end(), std::back_inserter(out));
        return out;
    }

    std::string to_string(double d)
    {
        return std::to_string(d);
    }

    std::string to_string(std::size_t s)
    {
        return std::to_string(s);
    }

    std::string to_string(int i)
    {
        return std::to_string(i);
    }

    std::string to_string(bool b)
    {
        return (b ? "true" : "false");
    }

    std::string format_variable(var_t variable)
    {
        std::string str = sutil::to_string(variable);
        if(str.find('.') == std::string::npos)
        {
            return str;
        }

        while(str[str.length() - 1] == '0')
        {
            str.pop_back();
            if(str[str.length() - 1] == '.')
            {
                str.pop_back();
                break;
            }
        }
        return str;
    }

    std::string remove_spaces(const std::string &str)
    {
        std::string result;
        result.reserve(str.size());

        for(auto& c : str)
        {
            if(c != ' ') result.push_back(c);
        }

        return result;
    }

    std::vector<std::string> split(const std::string& str, const std::string& delim)
    {
        std::size_t current_pos = 0;
        std::size_t prev_pos = 0;
        std::vector<std::string> result{};

        while((current_pos = str.find(delim, prev_pos)) != std::string::npos)
        {
            result.push_back(str.substr(prev_pos, current_pos - prev_pos));
            prev_pos = current_pos + delim.size();
        }

        result.push_back(str.substr(prev_pos));
        return result;
    }
}