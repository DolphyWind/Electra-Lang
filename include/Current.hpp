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
public:
    explicit Current(Direction direction);
    Current(Direction direction, Position position, StackPtr stackPtr);
    ~Current() = default;
    
    void setDirection(Direction direction);
    Direction getDirection();

    void setPosition(Position position);
    Position getPosition();

    void addVisitedPortal(Position position);
    std::optional<Position> popLastPortal();

    void setPortalStack(const std::stack<Position>& stack);
    [[nodiscard]] const std::stack<Position>& getPortalStack() const;
    [[nodiscard]] std::stack<Position>& getPortalStack();
    void iterate();

    StackPtr stackPtr{};
private:
    Direction m_direction = Direction::NONE;
    Position m_position = {0, 0};
    std::stack<Position> m_visitedPortalStack{};
};

typedef std::shared_ptr<Current> CurrentPtr;