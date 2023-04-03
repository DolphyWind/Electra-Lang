#include "Reverser.hpp"

bool Reverser::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    std::stack<var_t> newStack;
    while(!current->stackPtr->empty())
    {
        newStack.push(current->stackPtr->top());
        current->stackPtr->pop();
    }
    *current->stackPtr = newStack;
    defaultLogger.log(LogType::INFO, L"Reversed the entire stack.");

    return true;
}