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
#include <iostream>
#include <functional>
#include <stack>

// Pops 2 values from current's stackPtr and passes them into m_func. Then pushes result back to current's stackPtr.
// The first parameter that is popped is the first argument of m_func
// If there is less than two values or no values on current's stackPtr, it does nothing.
typedef std::function<var_t(var_t, var_t)> ArithmeticalFunc;

class ArithmeticalUnit : public Cable
{
    ArithmeticalFunc m_func;
public:
    ArithmeticalUnit(std::vector<Direction> directions, ArithmeticalFunc func):
        Cable(directions), m_func(func)
    {}
    ~ArithmeticalUnit() { };

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};