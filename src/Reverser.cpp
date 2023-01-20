#include "Reverser.hpp"

bool Reverser::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    std::stack<var_t> newStack;
    while(!m_stackPtr->empty())
    {
        newStack.push(m_stackPtr->top());
        m_stackPtr->pop();
    }
    *m_stackPtr = newStack;

    return true;
}