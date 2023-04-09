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

var_t popStack(StackPtr stack, var_t defaultValue)
{
    if(stack->empty())
    {
        defaultLogger.log(LogType::WARNING, L"The stack you tried to pop is empty. Returning {}.", defaultValue);
        return defaultValue;
    }

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