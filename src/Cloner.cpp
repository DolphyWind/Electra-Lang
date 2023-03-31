#include "Cloner.hpp"

bool Cloner::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(m_stackPtr->empty()) return true;
    
    var_t top = m_stackPtr->top();
    m_stackPtr->push(top);

    defaultLogger.log(LogType::INFO, "(Cloner) Pushing {} to stack.", top);
    return true;
}