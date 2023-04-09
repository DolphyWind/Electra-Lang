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

#include <Portal.hpp>

bool Portal::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    Direction currentDirection = current->getDirection();
    Position currentPos = current->getPosition();
    std::stack<Position> portalStack = current->getPortalStack();

    if(m_originalPosition != currentPos)
    {
        portalStack.push(currentPos);
        Position newPos = m_originalPosition + directionToPosition(currentDirection);
        CurrentPtr newCurrent = std::make_shared<Current>(currentDirection, newPos, current->stackPtr);
        newCurrent->setPortalStack(portalStack);
        currentVector->push_back(newCurrent);
        defaultLogger.log(LogType::INFO, L"Teleported current from ({}, {}) to ({}, {}).", currentPos.x, currentPos.y, newPos.x, newPos.y);
    }
    else
    {
        std::optional<Position> lastPortalPos = current->popLastPortal();
        if(!lastPortalPos.has_value()) return true;
        Position newPos = lastPortalPos.value() + directionToPosition(currentDirection);
        CurrentPtr newCurrent = std::make_shared<Current>(currentDirection, newPos, current->stackPtr);
        newCurrent->setPortalStack(current->getPortalStack());
        currentVector->push_back(newCurrent);
        defaultLogger.log(LogType::INFO, L"Teleported current from ({}, {}) to ({}, {}).", currentPos.x, currentPos.y, newPos.x, newPos.y);
    }
    
    return false;
}