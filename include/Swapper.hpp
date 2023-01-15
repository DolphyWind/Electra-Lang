#pragma once
#include <Cable.hpp>

// Swaps the top two values of m_stack

class Swapper : public Cable
{
    StackPtr m_stackPtr;
public:
    Swapper(std::vector<Direction> directions, StackPtr stackPtr):
        Cable(directions), m_stackPtr(stackPtr) {}
    ~Swapper(){};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};