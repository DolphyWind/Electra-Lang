#include "Cable.hpp"

bool Cable::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Component::work(current, currentVector))
        return false;

    Direction currentDir = current->getDirection();
    Position currentPos = current->getPosition();
    Position portalPos = current->getLastUsedPortalPosition();

    for(auto &dir : m_directions)
    {
        if(dir == currentDir || dir == invertDirection(currentDir)) continue;
        Position deltaPos = directionToPosition(dir);
        CurrentPtr newCurrent = std::make_shared<Current>(dir, currentPos + deltaPos);
        newCurrent->setLastUsedPortalPosition(portalPos);
        currentVector->push_back(newCurrent);
    }
    
    return true;
}