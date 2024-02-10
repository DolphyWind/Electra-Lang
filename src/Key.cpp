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

#include <Key.hpp>
#include <Logger.hpp>

Key::Key(const std::vector<Direction>& directions, const std::vector<Direction>& activatorDirections, std::vector<std::u32string>& sourceCode, char32_t transformTo):
    Cable(directions), m_activatorDirections(activatorDirections), m_sourceCode(sourceCode), m_transformTo(transformTo)
{}

bool Key::work(Current::Ptr current, std::vector<Current::Ptr>& currentVector)
{
    bool inActivatorDirections = false;
    Position curPos = current->getPosition();
    Direction curDirInv = invertDirection(current->getDirection());

    for(auto &d : m_activatorDirections)
    {
        if(d == curDirInv)
        {
            inActivatorDirections = true;
            break;
        }
    }

    if(inActivatorDirections)
    {
        m_sourceCode[curPos.y][curPos.x] = m_transformTo;
        defaultLogger.log(LogType::INFO, "(Key) Key at ({}, {}) is now activated.", curPos.x, curPos.y);
        return true;
    }

    if(!Component::work(current, currentVector))
    {
        return false;
    }

    // If not in activator directions move the current back
    Position newPos = curPos + directionToPosition(curDirInv);
    current->setPosition(newPos);
    defaultLogger.log(LogType::INFO, "(Key) Key at ({}, {}) is not activated. The current is being moved to ({}, {})", curPos.x, curPos.y, newPos.x, newPos.y);

    return Cable::work(current, currentVector);
}