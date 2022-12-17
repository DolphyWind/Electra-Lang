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
    m_directions.erase(std::remove(m_directions.begin(), m_directions.end(), currentDir), m_directions.end());
    for(auto &dir : m_directions)
        currentVector->push_back(std::make_shared<Current>(dir, currentPos));
    
    return true;
}