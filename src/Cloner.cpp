#include "Cloner.hpp"

bool Cloner::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(m_stackPtr->empty())
    {
        m_stackPtr->push(0);
        return true;
    }
    var_t top = m_stackPtr->top();
    m_stackPtr->push(top);

    defaultLogger.log(LogType::INFO, "(Cloner) Pushing " + std::to_string(top) + " to stack.");
    return true;
}