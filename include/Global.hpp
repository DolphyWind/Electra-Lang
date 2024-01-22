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
#include <stack>
#include <algorithm>
#include <string>
#include <vector>
#include <thirdparty/utfcpp/utf8.h>

typedef double var_t;
typedef std::stack<var_t>* StackPtr;
//typedef char32_t char_t;
typedef std::string string_t;

class Electra;
namespace Global
{
    // Pops the top value from the given stack. Returns defaultValue if the stack is empty.
    var_t popStack(StackPtr stack, var_t defaultValue = 0);

    // Removes unnecessary zeros in the mantissa
    std::string format_variable(var_t variable);

    // Removes spaces from a string
    std::string remove_spaces(const std::string& str);

    // Splits a string based on a given delimiter
    std::vector<std::string> split(const std::string& str, const std::string& delim);

    void safe_exit(int exit_code);

    // Empty struct
    struct Empty{};
}
