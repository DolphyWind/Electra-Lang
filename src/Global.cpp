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

#include <Global.hpp>
#include <Logger.hpp>
#include <cstring>

namespace Global
{
    var_t popStack(StackPtr stack, var_t defaultValue)
    {
        if(stack->empty()) return defaultValue;

        var_t top = stack->top();
        stack->pop();
        return top;
    }

    std::string format_variable(var_t variable)
    {
        std::string str = sconv::to_string(variable);
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

    void safe_exit(int exit_code)
    {
        // There used to be some code here

        std::exit(exit_code);
    }

} // namespace Global
