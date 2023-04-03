#include "Swapper.hpp"

bool Swapper::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(current->stackPtr->size() < 2)
        return true;

    var_t first = popStack(current->stackPtr);
    var_t second = popStack(current->stackPtr);
    current->stackPtr->push(first);
    current->stackPtr->push(second);

    defaultLogger.log(LogType::INFO, L"Swapping {} and {} on the stack.", first, second);

    return true;
}