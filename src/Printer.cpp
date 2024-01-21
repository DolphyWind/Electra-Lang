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

#include <Printer.hpp>

Printer::Printer(const std::vector<Direction>& directions, bool printAsChar):
    Cable(directions), m_printAsChar(printAsChar)
{}

bool Printer::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Component::work(current, currentVector))
        return false;
    
    if(current->stackPtr->empty()) return true;
    var_t top = Global::popStack(current->stackPtr);

    if(m_printAsChar)
    {
        std::wcout << (char_t)top << std::flush;
        defaultlogger.log(LogType::INFO, "Printed {} to screen.", std::wstring(1, (char_t)top));
    }
    else
    {
        std::wcout << Global::format_variable(top) << std::flush;
        defaultlogger.log(LogType::INFO, "Printed {} to screen.", top);
    }
    
    return Cable::work(current, currentVector);
}