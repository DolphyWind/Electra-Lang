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

#include <Generator.hpp>
#include <utility/Logger.hpp>

Generator::Generator(const std::vector<Direction>& directions, Position position):
    m_directions(directions), m_position(position)
{}

void Generator::generate(std::vector<Current::Ptr>& currentVector, StackPtr stackPtr)
{
    for(auto& dir : m_directions)
    {
        // Direction and position of the new current
        Position deltaPos = directionToPosition(dir);
        Position resultPos = m_position + deltaPos;

        currentVector.emplace_back(std::make_shared<Current>(dir, resultPos, stackPtr));
        defaultLogger.log(LogType::INFO, "Creating new current from a generator at ({},{}) with direction {}.", m_position.x, m_position.y, dir);
    }
}

const std::vector<Direction>& Generator::getDirections() const
{
    return m_directions;
}

std::vector<Direction>& Generator::getDirections()
{
    return m_directions;
}
