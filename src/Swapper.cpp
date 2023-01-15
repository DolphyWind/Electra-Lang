#include "Swapper.hpp"

bool Swapper::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(m_stackPtr->size() < 2)
        return true;

    var_t first = popStack(m_stackPtr);
    var_t second = popStack(m_stackPtr);
    m_stackPtr->push(first);
    m_stackPtr->push(second);

    return true;
}