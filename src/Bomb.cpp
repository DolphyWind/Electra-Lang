#include <Bomb.hpp>

bool Bomb::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    *m_isRunningPtr = false;
    return true;
}