#include "Remover.hpp"

bool Remover::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    popStack(m_stackPtr);
    return true;
}