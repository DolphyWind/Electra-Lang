#pragma once
#include <Cable.hpp>

class Reverser : public Cable
{
    StackPtr m_stackPtr;
public:
    Reverser(std::vector<Direction> directions, StackPtr stackPtr):
        Cable(directions), m_stackPtr(stackPtr)
    {}
    ~Reverser(){};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};