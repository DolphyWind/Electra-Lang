#include "Cable.hpp"

bool Cable::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Component::work(current, currentVector))
        return false;

    Direction currentDir = current->getDirection();
    Position currentPos = current->getPosition();
    std::stack<Position> portalStack = current->getPortalStack();

    for(auto &dir : m_directions)
    {
        if(dir == currentDir || dir == invertDirection(currentDir)) continue;
        Position deltaPos = directionToPosition(dir);
        CurrentPtr newCurrent = std::make_shared<Current>(dir, currentPos + deltaPos);
        newCurrent->setPortalStack(portalStack);
        currentVector->push_back(newCurrent);
    }
    
    return true;
}