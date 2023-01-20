#include "Portal.hpp"

bool Portal::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    Direction currentDirection = current->getDirection();
    Position currentPos = current->getPosition();
    Position lastPortalPos = current->getLastUsedPortalPosition();

    if(m_originalPosition != currentPos)
    {
        CurrentPtr newCurrent = std::make_shared<Current>(currentDirection, m_originalPosition + directionToPosition(currentDirection));
        newCurrent->setLastUsedPortalPosition(currentPos);
        currentVector->push_back(newCurrent);
    }
    else
    {
        if(lastPortalPos == Position({-1, -1})) return true;
        CurrentPtr newCurrent = std::make_shared<Current>(currentDirection, lastPortalPos + directionToPosition(currentDirection));
        newCurrent->setLastUsedPortalPosition(currentPos);
        currentVector->push_back(newCurrent);
    }
    
    return false;
}