#include "Cloner.hpp"

bool Cloner::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(current->stackPtr->empty()) return true;
    
    var_t top = current->stackPtr->top();
    current->stackPtr->push(top);

    defaultLogger.log(LogType::INFO, L"(Cloner) Pushing {} to stack.", top);
    return true;
}