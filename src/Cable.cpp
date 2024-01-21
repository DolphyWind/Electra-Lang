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

#include <Cable.hpp>

Cable::Cable(const std::vector<Direction>& directions, bool is_one_directional):
    Component(directions), m_is_one_directional(is_one_directional)
{};

bool Cable::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Component::work(current, currentVector))
    {
        defaultlogger.log(LogType::INFO, "The current at ({}, {}) with direction {} is not in the supported list of directions. Supported directions are: {}.",
        current->getPosition().x, current->getPosition().y, current->getDirection(), this->m_directions);
        return false;
    }

    Direction currentDir = current->getDirection();
    Position currentPos = current->getPosition();
    std::stack<Position> portalStack = current->getPortalStack();

    for(auto &dir : m_directions)
    {
        if(dir == currentDir || dir == invertDirection(currentDir)) continue;
        Position deltaPos = directionToPosition(dir);
        CurrentPtr newCurrent = std::make_shared<Current>(dir, currentPos + deltaPos, current->stackPtr);
        newCurrent->setPortalStack(portalStack);
        currentVector->push_back(newCurrent);
    }
    // std::wcout << std::to_wstring(currentDir) << std::endl;
    // std::wcout << std::to_wstring(m_directions) << std::endl;
    return m_is_one_directional || (std::find(m_directions.begin(), m_directions.end(), currentDir) != this->m_directions.end());
}