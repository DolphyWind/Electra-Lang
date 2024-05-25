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
#include <components/Cable.hpp>

// Moves current's stackPtr pointer forwards or backwards.
// If moveValue is true, it pops the top value before moving the stackPtr and pushes that value to the new stack after moving.
// It does not push anything if there is nothing to pop.
class StackSwitcher : public Cable
{
public:
    StackSwitcher(const std::vector<Direction>& directions, bool moveForward, std::vector<std::stack<var_t>>* stacks, bool moveValue);
    ~StackSwitcher() override = default;

    bool work(Current::Ptr& current, std::vector<Current::Ptr>& currentVector) override;
private:
    std::vector<std::stack<var_t>>* m_stacks;
    bool m_moveForward = true;
    bool m_moveValue = false;
};
