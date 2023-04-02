#pragma once
#include <Cable.hpp>

// Swaps the top two values of m_stack

class Swapper : public Cable
{
public:
    Swapper(std::vector<Direction> directions):
        Cable(directions) {}
    ~Swapper(){};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};