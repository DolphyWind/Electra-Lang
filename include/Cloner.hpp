#pragma once
#include <Cable.hpp>
// Pops the top value of the stack and pushes it back onto stack.
// If there is no top value it does nothing

class Cloner : public Cable
{
public:
    Cloner(std::vector<Direction> directions):
    Cable(directions)
    {};
    ~Cloner() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};