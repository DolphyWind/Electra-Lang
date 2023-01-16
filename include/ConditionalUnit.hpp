#pragma once
#include <Cable.hpp>

// Pops the value on top of the stack, if killSignal is true and top == targetValue it kills the current.
// if killSignal is false and top == targetValue it pushes 1 to stack
// if killSignal is false and top != targetValue it pushes 0 to stack
// Does nothing if there is no value at the top

class ConditionalUnit : public Cable
{
    StackPtr m_stackPtr;
    var_t m_targetValue;
    bool m_killSignal;
public:
    ConditionalUnit(std::vector<Direction> directions, StackPtr stackPtr, var_t targetValue, bool killSignal):
        Cable(directions), m_stackPtr(stackPtr), m_targetValue(targetValue), m_killSignal(killSignal)
    {}
    ~ConditionalUnit() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};