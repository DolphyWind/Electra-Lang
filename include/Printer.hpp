#pragma once
#include <Cable.hpp>
#include <iostream>
#include <stack>
#include <direction.hpp>

// Pops the value on top of the stack and prints it on screen as number. If m_printAsUchar is true it prints it as a char_t.
// If there is no top value, it does nothing.

class Printer : public Cable
{
private:
    StackPtr m_stackPtr;
    bool m_printAsChar = false;
public:
    Printer(std::vector<Direction> directions, StackPtr stackPtr, bool printAsChar):
        Cable(directions), m_stackPtr(stackPtr), m_printAsChar(printAsChar)
    {

    }
    ~Printer() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};