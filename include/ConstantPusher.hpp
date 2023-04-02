#pragma once
#include <Cable.hpp>

// Pushes m_constant to the stack.
// If m_getInput is true, ignores the default value of m_constant and gets input from user.

class ConstantPusher : public Cable
{
    bool m_getInput = false;
    bool m_getInputAsChar = false;
    var_t m_constant;
public:
    ConstantPusher(std::vector<Direction> directions, bool getInput, bool getInputAsChar, var_t constant):
        Cable(directions), m_getInput(getInput), m_getInputAsChar(getInputAsChar), m_constant(constant)
    {}
    ~ConstantPusher() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};