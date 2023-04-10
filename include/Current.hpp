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

#pragma once
#include <iostream>
#include <direction.hpp>
#include <Global.hpp>
#include <memory>
#include <stack>
#include <optional>

// Instruction pointers that act like the currents in electricity
class Current
{
private:
    Direction m_direction;
    Position m_position = {0, 0};
    std::stack<Position> m_visitedPortalStack;
    
public:
    Current(Direction direction): m_direction(direction) {};
    Current(Direction direction, Position position, StackPtr stackPtr): m_position(position), m_direction(direction), stackPtr(stackPtr) {};
    ~Current() {};
    
    inline void setDirection(Direction direction) {m_direction = direction;}
    inline Direction getDirection() {return m_direction;}
    inline void setPosition(Position position) {m_position = position;}
    inline Position getPosition() {return m_position;}
    void addVisitedPortal(Position position);
    std::optional<Position> popLastPortal();
    inline void setPortalStack(const std::stack<Position>& stack) {m_visitedPortalStack = stack;}
    inline std::stack<Position> getPortalStack() {return m_visitedPortalStack;};
    void iterate();

    StackPtr stackPtr;
};

typedef std::shared_ptr<Current> CurrentPtr;