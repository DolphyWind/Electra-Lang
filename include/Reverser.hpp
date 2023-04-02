#pragma once
#include <Cable.hpp>

class Reverser : public Cable
{
public:
    Reverser(std::vector<Direction> directions):
        Cable(directions)
    {}
    ~Reverser(){};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};