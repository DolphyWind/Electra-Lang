#pragma once
#include <Cable.hpp>
#include <iostream>
#include <functional>
#include <stack>

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