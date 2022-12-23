#include "Component.hpp"

bool Component::work(CurrentPtr current, std::vector<CurrentPtr> *currentPtr)
{
    for(auto &d : m_directions)
    {
        if(d == current->getDirection()) return true;
    }
    std::cout << (int) current->getDirection() << std::endl;
    return false;
}