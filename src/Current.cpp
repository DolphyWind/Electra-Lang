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

#include <Current.hpp>

Current::Current(Direction direction):
    m_direction(direction)
{}

Current::Current(Direction direction, Position position, StackPtr stackPtr):
    m_position(position), m_direction(direction), stackPtr(stackPtr)
{}

void Current::iterate()
{
    m_position = m_position + directionToPosition(m_direction);
}

void Current::setDirection(Direction direction)
{
    m_direction = direction;
}

Direction Current::getDirection()
{
    return m_direction;
}

void Current::setPosition(Position position)
{
    m_position = position;
}

Position Current::getPosition()
{
    return m_position;
}

void Current::addVisitedPortal(Position position)
{
    m_visitedPortalStack.push(position);
}

std::optional<Position> Current::popLastPortal()
{
    if(m_visitedPortalStack.empty())
    {
        return std::nullopt;
    }
    
    Position top = m_visitedPortalStack.top();
    m_visitedPortalStack.pop();
    return top;
}

void Current::setPortalStack(const std::stack<Position>& stack)
{
    m_visitedPortalStack = stack;
}

const std::stack<Position>& Current::getPortalStack() const
{
    return m_visitedPortalStack;
}

std::stack<Position>& Current::getPortalStack()
{
    return m_visitedPortalStack;
}