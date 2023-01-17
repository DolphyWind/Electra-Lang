#include "Portal.hpp"

bool Portal::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    for(auto &p : m_allCopies)
    {
        Direction currentDirection = current->getDirection();
        Position currentPos = current->getPosition();

        if(p != currentPos)
            currentVector->push_back(std::make_shared<Current>(currentDirection, p + directionToPosition(currentDirection)));
    }
    return false;
}