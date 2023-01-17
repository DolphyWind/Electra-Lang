#include "ConditionalUnit.hpp"

bool ConditionalUnit::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(m_stackPtr->empty())
        return true;
    
    var_t x = m_stackPtr->top();
    bool condition = (x == m_targetValue);
    if(m_invert) condition = !condition;

    return !condition;
}