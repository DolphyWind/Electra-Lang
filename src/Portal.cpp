#include "Portal.hpp"

bool Portal::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    Direction currentDirection = current->getDirection();
    Position currentPos = current->getPosition();
    std::stack<Position> portalStack = current->getPortalStack();

    if(m_originalPosition != currentPos)
    {
        portalStack.push(currentPos);
        CurrentPtr newCurrent = std::make_shared<Current>(currentDirection, m_originalPosition + directionToPosition(currentDirection));
        newCurrent->setPortalStack(portalStack);
        currentVector->push_back(newCurrent);
    }
    else
    {
        std::optional<Position> lastPortalPos = current->popLastPortal();
        if(!lastPortalPos.has_value()) return true;
        CurrentPtr newCurrent = std::make_shared<Current>(currentDirection, lastPortalPos.value() + directionToPosition(currentDirection));
        newCurrent->setPortalStack(current->getPortalStack());
        currentVector->push_back(newCurrent);
    }
    
    return false;
}