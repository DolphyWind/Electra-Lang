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
    {
        return false;
    }

    if(current->stackPtr->empty()) return true;
    var_t top = Global::popStack(current->stackPtr);

    if(m_printAsChar)
    {
        std::u32string u32str(1, static_cast<char32_t>(top));
        std::string str_to_print;
        utf8::utf32to8(u32str.begin(), u32str.end(), std::back_inserter(str_to_print));

        std::cout << str_to_print << std::flush;
        defaultlogger.log(LogType::INFO, "Printed {} to screen.", std::u32string(1, static_cast<char32_t>(top)));
    }
    else
    {
        std::cout << sutil::format_variable(top) << std::flush;
        defaultlogger.log(LogType::INFO, "Printed {} to screen.", top);
    }
    
    return Cable::work(current, currentVector);
}