#include "ArithmeticalUnit.hpp"

bool ArithmeticalUnit::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector)) return false;
    
    if(current->stackPtr->size() < 2) return true;
    
    var_t first, second;
    
    first = popStack(current->stackPtr);
    second = popStack(current->stackPtr);

    var_t result = m_func(first, second);
    current->stackPtr->push(result);
    
    defaultLogger.log(LogType::INFO, L"(ArithmeticalUnit) Passing {} and {} into an arithmetical unit. The result is: {}", first, second, result);
    return true;
}