#pragma once
#include <Cable.hpp>
#include <iostream>
#include <stack>
#include <direction.hpp>

// Pops the value on top of the stack and prints it on screen as number. If m_printAsAscii is true it prints it as a char.

class Printer : public Cable
{
private:
    StackPtr m_stackPtr;
    bool m_printAsAscii = false;
public:
    Printer(std::vector<Direction> directions, StackPtr stackPtr, bool printAsAscii):
        Cable(directions), m_stackPtr(stackPtr), m_printAsAscii(printAsAscii)
    {

    };
    ~Printer() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};