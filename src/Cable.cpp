#include "Cable.hpp"

bool Cable::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Component::work(current, currentVector))
        return false;

    Direction currentDir = current->getDirection();
    Position currentPos = current->getPosition();
    
    for(auto &dir : m_directions)
    {
        if(dir == currentDir || dir == invertDirection(currentDir)) continue;
        Position deltaPos = directionToPosition(dir);
        currentVector->push_back(std::make_shared<Current>(dir, currentPos + deltaPos));
    }
    
    return true;
}