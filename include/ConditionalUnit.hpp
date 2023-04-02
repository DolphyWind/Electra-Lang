#pragma once
#include <Cable.hpp>

// Pops the value on top of the stack, if top==targetValue it kills the signal if invert is false.
// If invert is true, it kills the signal when top!=targetValue

class ConditionalUnit : public Cable
{
    var_t m_targetValue;
    bool m_invert;
public:
    ConditionalUnit(std::vector<Direction> directions, var_t targetValue, bool invert):
        Cable(directions), m_targetValue(targetValue), m_invert(invert)
    {}
    ~ConditionalUnit() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};