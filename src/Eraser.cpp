#include <Eraser.hpp>

bool Eraser::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    defaultLogger.log(LogType::INFO, "Removed {} from stack.", popStack(current->stackPtr));
    return true;
}