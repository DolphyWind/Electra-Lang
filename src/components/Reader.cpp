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
#include <sstream>

#include <components/Reader.hpp>
#include <utility/Logger.hpp>

Reader::Reader(const std::vector<Direction>& directions, bool getInputAsChar, Electra& electra):
    Cable(directions), m_getInputAsChar(getInputAsChar), m_interpreter(electra)
{}

bool Reader::work(Current::Ptr& current, std::vector<Current::Ptr>& currentVector)
{
    if(!Component::work(current, currentVector))
    {
        return false;
    }
    
    if(m_getInputAsChar)
    {
	    std::stringstream readSS;
        std::u32string combinedStr;

        char firstChar;
        std::cin >> firstChar;
        if (std::cin.eof())
        {
            current->stackPtr->push(0);
            return Cable::work(current, currentVector);
        }

        readSS << firstChar;
        if (firstChar < 0)
        {
            if (firstChar >= -64)
            {
                char secondChar;
                std::cin >> secondChar;

                readSS << secondChar;
            }
            if (firstChar >= -32)
            {
                char thirdChar;
                std::cin >> thirdChar;

                readSS << thirdChar;
            }
            if (firstChar >= -16)
            {
                char fourthChar;
                std::cin >> fourthChar;

                readSS << fourthChar;
            }
        }

        std::string readStr = readSS.str();
        utf8::utf8to32(readStr.begin(), readStr.end(), std::back_inserter(combinedStr));

        current->stackPtr->push(static_cast<var_t>(combinedStr[0]));
        defaultLogger.log(LogType::INFO, "(Reader) Read {} from user and pushed onto stack.", readSS.str());
    }
    else
    {
        var_t v;
#ifdef HAS_VISUAL_MODE
        if(m_interpreter.getVisualModeManager().isSetup())
        {
            std::string input = m_interpreter.getVisualModeManager().getVIOH().take_input();
            v = std::stod(input);
        }
        else
        {
#endif
        std::cin >> v;
        if(std::cin.eof())
        {
            v = 0;
        }
#ifdef HAS_VISUAL_MODE
        }
#endif
        current->stackPtr->push(v);
        defaultLogger.log(LogType::INFO, "(Reader) Read {} from user and pushed onto stack.", v);
    }
    return Cable::work(current, currentVector);
}
