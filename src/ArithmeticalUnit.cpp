#include "ArithmeticalUnit.hpp"

bool ArithmeticalUnit::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    var_t first, second;
    
    first = popStack(m_stackPtr);
    second = popStack(m_stackPtr);

    var_t result = m_func(first, second);
    m_stackPtr->push(result);
    
    
    return true;
}