#include "Remover.hpp"

bool Remover::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    defaultLogger.log(LogType::INFO, "Removed {} from stack.", popStack(m_stackPtr));
    return true;
}