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

namespace Global
{
    var_t popStack(StackPtr stack, var_t defaultValue)
    {
        if(stack->empty()) return defaultValue;

        var_t top = stack->top();
        stack->pop();
        return top;
    }

    std::wstring format_variable(var_t variable)
    {
        std::wstring wstr = std::to_wstring(variable);
        if(wstr.find(L'.') == std::wstring::npos) return wstr;
        
        while(wstr[wstr.length() - 1] == L'0')
        {
            wstr.pop_back();
            if(wstr[wstr.length() - 1] == L'.')
            {
                wstr.pop_back();
                break;
            }
        }
        return wstr;
    }

    std::wstring remove_spaces(const std::wstring &wstr)
    {
        std::wstring result;
        for(auto &c : wstr)
        {
            if(c != L' ') result.push_back(c);
        }

        return result;
    }

    std::vector<std::string> split(const std::string& str, const std::string& delim) 
    {
        std::vector<std::string> tokens;
        std::size_t prev = 0, pos = 0;
        do
        {
            pos = str.find(delim, prev);
            if(pos == std::string::npos) pos = str.length();
            std::string token = str.substr(prev, pos-prev);
            tokens.push_back(token);
            prev = pos + delim.length();
        } while (pos < str.length() && prev < str.length());
        return tokens;
    }

    std::vector<std::wstring> split_wstr(const std::wstring& str, const std::wstring& delim)
    {
        std::vector<std::wstring> tokens;
        std::size_t prev = 0, pos = 0;
        do
        {
            pos = str.find(delim, prev);
            if(pos == std::string::npos) pos = str.length();
            std::wstring token = str.substr(prev, pos-prev);
            tokens.push_back(token);
            prev = pos + delim.length();
        } while (pos < str.length() && prev < str.length());
        return tokens;
    }

    std::wstring replaceString(std::wstring& originalStr, const std::wstring& lookFor, const std::wstring& replaceWith)
    {
        std::size_t pos = originalStr.find(lookFor);
        if(pos == std::wstring::npos)
            return originalStr;
        
        return originalStr.replace(pos, lookFor.length(), replaceWith);
    }
} // namespace Global
