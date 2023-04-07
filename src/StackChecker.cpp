#include "Cable.hpp"
#include <StackChecker.hpp>

bool StackChecker::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(current->stackPtr->empty()) return m_returnIfEmpty;
    return !m_returnIfEmpty;
}