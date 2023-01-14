#include "Cable.hpp"

bool Cable::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Component::work(current, currentVector))
        return false;

    Direction currentDir = current->getDirection();
    Position currentPos = current->getPosition();

    std::vector<Direction> copyDirections = m_directions;
    copyDirections.erase(std::remove(copyDirections.begin(), copyDirections.end(), currentDir), copyDirections.end());
    copyDirections.erase(std::remove(copyDirections.begin(), copyDirections.end(), invertDirection(currentDir)), copyDirections.end());
    for(auto &dir : copyDirections)
    {
        Position deltaPos = directionToPosition(dir);
        currentVector->push_back(std::make_shared<Current>(dir, currentPos + deltaPos));
    }
    
    return true;
}