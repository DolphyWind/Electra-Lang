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

#include <iostream>

#include <components/Printer.hpp>
#include <utility/Logger.hpp>

Printer::Printer(const std::vector<Direction>& directions, bool printAsChar, Electra& electra):
    Cable(directions), m_printAsChar(printAsChar), m_interpreter(electra)
{}

bool Printer::work(Current::Ptr& current, std::vector<Current::Ptr>& currentVector)
{
    if(!Component::work(current, currentVector))
    {
        return false;
    }

    if(current->stackPtr->empty())
    {
        return Cable::work(current, currentVector);
    }
    var_t top = Global::popStack(current->stackPtr);

    if(m_printAsChar)
    {
        auto top_character32 = static_cast<char32_t>(top);
        std::u32string u32str(1, top_character32);
    std::string str_to_print;
        try
        {
            utf8::utf32to8(u32str.begin(), u32str.end(), std::back_inserter(str_to_print));
        }
        catch(const utf8::invalid_code_point& invalidCodePoint)
        {
            char charToPrint = static_cast<char>(top_character32);

#ifdef HAS_VISUAL_MODE
            if(!m_interpreter.getVisualModeManager().isSetup())
            {
#endif
                std::cout << charToPrint << std::flush;
#ifdef HAS_VISUAL_MODE
            }
            else
            {
                m_interpreter.getVisualModeManager().getVIOH().print(charToPrint);
            }
#endif
        }

#ifdef HAS_VISUAL_MODE
        if(!m_interpreter.getVisualModeManager().isSetup())
        {
#endif
            std::cout << str_to_print << std::flush;
#ifdef HAS_VISUAL_MODE
        }
        else
        {
            m_interpreter.getVisualModeManager().getVIOH().print(str_to_print);
        }
#endif
        defaultLogger.log(LogType::INFO, "Printed {} to screen.", std::u32string(1, static_cast<char32_t>(top)));
    }
    else
    {
        std::string str_to_print = sutil::format_variable(top);
#ifdef HAS_VISUAL_MODE
        if(!m_interpreter.getVisualModeManager().isSetup())
        {
#endif
            std::cout << str_to_print << std::flush;
#ifdef HAS_VISUAL_MODE
        }
        else
        {
            m_interpreter.getVisualModeManager().getVIOH().print(str_to_print);
        }
#endif
        defaultLogger.log(LogType::INFO, "Printed {} to screen.", top);
    }
    
    return Cable::work(current, currentVector);
}
