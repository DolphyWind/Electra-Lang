#include "Cable.hpp"

Cable::~Cable()
{

}

bool Cable::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Component::work(current, currentVector))
        return false;

    Direction currentDir = current->getDirection();
    Position currentPos = current->getPosition();
    Position deltaPos = directionToPosition(currentDir);

    std::vector<Direction> copyDirections = m_directions;
    copyDirections.erase(std::remove(copyDirections.begin(), copyDirections.end(), currentDir), copyDirections.end());
    copyDirections.erase(std::remove(copyDirections.begin(), copyDirections.end(), invertDirection(currentDir)), copyDirections.end());
    for(auto &dir : copyDirections)
        currentVector->push_back(std::make_shared<Current>(dir, currentPos + deltaPos));
    
    return true;
}