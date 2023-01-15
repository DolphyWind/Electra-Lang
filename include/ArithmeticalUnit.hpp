#pragma once
#include <Cable.hpp>
#include <iostream>
#include <functional>
#include <stack>

// Pops 2 values from stack and passes them into m_func. Then pushes result back to stack.
// If there is no two values on stack, it does nothing.

typedef std::function<var_t(var_t, var_t)> ArithmeticalFunc;

class ArithmeticalUnit : public Cable
{
    ArithmeticalFunc m_func;
    StackPtr m_stackPtr;
public:
    ArithmeticalUnit(std::vector<Direction> directions, std::stack<var_t> *stackPtr, ArithmeticalFunc func):
        Cable(directions), m_stackPtr(stackPtr), m_func(func)
    {

    }
    ~ArithmeticalUnit() { };

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};