#pragma once
#include <Cable.hpp>

// Pops the top value from the current stack
class Eraser : public Cable
{
public:
    Eraser(std::vector<Direction> directions):
        Cable(directions) {}
    ~Eraser() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};