#include "Current.hpp"
#include <StackSwitcher.hpp>

bool StackSwitcher::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(m_moveForward)
    {
        if((++current->stackPtr) == &(*m_stacks->end())) current->stackPtr = &(*m_stacks->begin());
    }
    else
    {
        if(current->stackPtr == &(*m_stacks->begin())) current->stackPtr = &(*(m_stacks->end() - 1));
    }

    return true;
}