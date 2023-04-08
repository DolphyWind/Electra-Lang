#include <Component.hpp>

bool Component::work(CurrentPtr current, std::vector<CurrentPtr> *currentPtr)
{
    for(auto &d : m_directions)
    {
        if(invertDirection(d) == current->getDirection()) return true;
    }
    return false;
}