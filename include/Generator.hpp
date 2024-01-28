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
#include <direction.hpp>
#include <iostream>
#include <vector>
#include <Current.hpp>
#include <memory>
#include <Logger.hpp>
#include <stack>
#include <Global.hpp>

// Generates currents at the start of the program.
class Generator
{
public:
    Generator(const std::vector<Direction>& directions, Position position);
    ~Generator() = default;

    /// @brief Generates new current if it can
    /// @param currentVector Pushes the new current in this vector
    void generate(std::vector<CurrentPtr> *currentVector, StackPtr stackPtr);

    [[nodiscard]] const std::vector<Direction>& getDirections() const;
    std::vector<Direction>& getDirections();
private:
    Position m_position;
    std::vector<Direction> m_directions;
};

typedef std::shared_ptr<Generator> GeneratorPtr;