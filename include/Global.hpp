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
#include <Logger.hpp>

typedef double var_t;
typedef std::stack<var_t>* StackPtr;
typedef wchar_t char_t;

namespace Global
{

    // Pops the top value of stack. Returns defaultValue if there is no item.
    var_t popStack(StackPtr stack, var_t defaultValue = 0);

    // Removes unnecessery zeros in the mantissa
    std::wstring format_variable(var_t variable);

    // Removes spaces from wstring
    std::wstring remove_spaces(const std::wstring& wstr);

    // Splits a string based on a given delimiter
    std::vector<std::string> split(const std::string& str, const std::string& delim);

    // Splits a wstring based on a given delimeter
    std::vector<std::wstring> split_wstr(const std::wstring& str, const std::wstring& delim);

    // Replaces "lookFor" with "replaceWith" in "originalStr"
    std::wstring replaceString(std::wstring& originalStr, const std::wstring& lookFor, const std::wstring& replaceWith);
}
