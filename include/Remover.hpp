#pragma once
#include <Cable.hpp>

// Pops the top value from m_stack

class Remover : public Cable
{
    StackPtr m_stackPtr;
public:
    Remover(std::vector<Direction> directions, StackPtr stackPtr):
        Cable(directions), m_stackPtr(stackPtr) {}
    ~Remover() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};