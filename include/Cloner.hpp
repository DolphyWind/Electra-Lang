#pragma once
#include <Cable.hpp>
// Pops the top value of the stack and pushes it back onto stack.
// If there is no top value it pushes zero to the stack

class Cloner : public Cable
{
    StackPtr m_stackPtr;
public:
    Cloner(std::vector<Direction> directions, StackPtr stackPtr):
    Cable(directions), m_stackPtr(stackPtr)
    {};
    ~Cloner() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};