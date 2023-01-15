#pragma once
#include <Cable.hpp>

// Pops the value on top of the stack adds m_constant to it and pushes it back to the stack.
// If there is no value on the stack, it does nothing.

class ConstantAdder : public Cable
{
    StackPtr m_stackPtr;
    var_t m_constant;
public:
    ConstantAdder(std::vector<Direction> directions, StackPtr stackPtr, var_t constant):
        Cable(directions), m_stackPtr(stackPtr), m_constant(constant)
    {}
    ~ConstantAdder() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};