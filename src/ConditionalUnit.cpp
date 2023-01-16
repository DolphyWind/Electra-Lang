#include "ConditionalUnit.hpp"

bool ConditionalUnit::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(m_stackPtr->empty())
        return true;
    
    var_t x = m_stackPtr->top();
    if (x == m_targetValue)
    {
        if(m_killSignal) return false;
        m_stackPtr->push(1);
    }
    else if(!m_killSignal)
        m_stackPtr->push(0);

    return true;
}