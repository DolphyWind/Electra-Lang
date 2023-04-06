#pragma once
#include <Cable.hpp>

// Pushes m_constant to the stack.

class ConstantPusher : public Cable
{
    var_t m_constant;
public:
    ConstantPusher(std::vector<Direction> directions, var_t constant):
        Cable(directions), m_constant(constant)
    {}
    ~ConstantPusher() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};