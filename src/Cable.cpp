#include <Cable.hpp>

bool Cable::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Component::work(current, currentVector))
    {
        defaultLogger.log(LogType::INFO, L"The current at ({}, {}) with direction {} is not in the supported list of directions. Supported directions are: {}.",
        current->getPosition().x, current->getPosition().y, current->getDirection(), this->m_directions);
        return false;
    }

    Direction currentDir = current->getDirection();
    Position currentPos = current->getPosition();
    std::stack<Position> portalStack = current->getPortalStack();

    for(auto &dir : m_directions)
    {
        if(dir == currentDir || dir == invertDirection(currentDir)) continue;
        Position deltaPos = directionToPosition(dir);
        CurrentPtr newCurrent = std::make_shared<Current>(dir, currentPos + deltaPos, current->stackPtr);
        newCurrent->setPortalStack(portalStack);
        currentVector->push_back(newCurrent);
    }
    
    return true;
}