#include "ConditionalUnit.hpp"

bool ConditionalUnit::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(m_stackPtr->empty())
        return true;
    
    var_t x = popStack(m_stackPtr);
    bool condition = (x == m_targetValue);

    if(condition) defaultLogger.log(LogType::INFO, "(ConditionalUnit) {} is equals to {}.", x, m_targetValue);
    else defaultLogger.log(LogType::INFO, "(ConditionalUnit) {} is not equals to {}.", x, m_targetValue);

    
    if(m_invert) condition = !condition;
    if(!condition) defaultLogger.log(LogType::INFO, "(ConditionalUnit) Current will pass.");
    else defaultLogger.log(LogType::INFO, "(ConditionalUnit) Current will not pass.");

    return !condition;
}