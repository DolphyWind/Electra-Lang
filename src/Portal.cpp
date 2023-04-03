#include "Portal.hpp"

bool Portal::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    Direction currentDirection = current->getDirection();
    Position currentPos = current->getPosition();
    std::stack<Position> portalStack = current->getPortalStack();

    if(m_originalPosition != currentPos)
    {
        portalStack.push(currentPos);
        Position newPos = m_originalPosition + directionToPosition(currentDirection);
        CurrentPtr newCurrent = std::make_shared<Current>(currentDirection, newPos, current->stackPtr);
        newCurrent->setPortalStack(portalStack);
        currentVector->push_back(newCurrent);
        defaultLogger.log(LogType::INFO, L"Teleported current from ({}, {}) to ({}, {}).", currentPos.x, currentPos.y, newPos.x, newPos.y);
    }
    else
    {
        std::optional<Position> lastPortalPos = current->popLastPortal();
        if(!lastPortalPos.has_value()) return true;
        Position newPos = lastPortalPos.value() + directionToPosition(currentDirection);
        CurrentPtr newCurrent = std::make_shared<Current>(currentDirection, newPos, current->stackPtr);
        newCurrent->setPortalStack(current->getPortalStack());
        currentVector->push_back(newCurrent);
        defaultLogger.log(LogType::INFO, L"Teleported current from ({}, {}) to ({}, {}).", currentPos.x, currentPos.y, newPos.x, newPos.y);
    }
    
    return false;
}