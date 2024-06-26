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

#pragma once

#include <vector>
#include <string>
#include <Direction.hpp>
#include <utility/Global.hpp>
#include <optional>
#include <thirdparty/utfcpp/utf8.h>
#include <boost/regex.hpp>

namespace sutil
{
    std::string to_string(const Direction& direction);
    std::string to_string(const std::vector<Direction>& directions);
    std::string to_string(const std::string& str);
    std::string to_string(const std::u32string& str);
    std::string to_string(double d);
    std::string to_string(std::size_t s);
    std::string to_string(int i);
    std::string to_string(long l);
    std::string to_string(bool b);

    // Removes unnecessary zeros in the fractional part
    std::string format_variable(var_t variable);

    // Removes spaces from a string
    std::string remove_spaces(const std::string& str);

    // Splits a string based on a given delimiter
    std::vector<std::string> split(const std::string& str, const std::string& delim);

    // Removes electra comments from given line
    void remove_comments(std::string& line);

    // Performs a regex search on given text with given regex pattern and returns the matching string if a match occurs
    std::optional<std::string> get_matched_string(const std::string& text, const boost::regex& pattern);
}
