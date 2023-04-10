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
#include <Cable.hpp>

// Pops the value on top of the current's stackPtr, and compares it with m_targetValue. If the result is true, lets current pass.
// Otherwise kills the current. Inverted Conditional units does the opposite.
class ConditionalUnit : public Cable
{
    var_t m_targetValue;
    bool m_invert;
    bool m_checkEqual;
    bool m_checkLess;
    bool m_checkGreater;
public:
    ConditionalUnit(std::vector<Direction> directions, var_t targetValue, bool invert, bool checkEqual, bool checkLess, bool checkGreater):
        Cable(directions), m_targetValue(targetValue), m_invert(invert), m_checkEqual(checkEqual), m_checkLess(checkLess), m_checkGreater(checkGreater)
    {}
    ~ConditionalUnit() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};