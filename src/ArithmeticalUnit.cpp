#include "ArithmeticalUnit.hpp"

bool ArithmeticalUnit::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(m_stackPtr->size() < 2) return true;
    
    var_t first, second;
    
    first = popStack(m_stackPtr);
    second = popStack(m_stackPtr);

    var_t result = m_func(first, second);
    m_stackPtr->push(result);
    
    defaultLogger.log(LogType::INFO, "(ArithmeticalUnit) Passing" + std::to_string(first) + " and " + std::to_string(second) + " into an arithmetical unit. "
    + "The result is: " + std::to_string(result));
    return true;
}