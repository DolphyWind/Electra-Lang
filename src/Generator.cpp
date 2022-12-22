#include "Generator.hpp"

Generator::~Generator()
{

}

void Generator::update(std::vector<CurrentPtr> *currentVector)
{
    if(m_directions.empty()) return;
    if(!isActive()) return;
    if(m_child != nullptr)
    {
        if(!m_child->getDestroyed()) return;
    }
    m_generatedOnce = true;

    Direction dir = m_directions[m_directionIndex];
    Position deltaPos = directionToPosition(dir);
    Position resultPos = {0, 0};
    resultPos = m_position + deltaPos;

    m_child = std::make_shared<Current>(dir, resultPos);
    currentVector->push_back(m_child);

    m_directionIndex ++;
    if(m_directionIndex >= m_directions.size()) m_directionIndex = 0;
    
}

bool Generator::isActive()
{
    if(!m_isEnabled) return false;
    if(m_generatedOnce && m_workOnce) return false;
    return true;
}

bool Generator::checkToggle(CurrentPtr current)
{
    if(m_position != current->getPosition()) return false;

    Direction dir = current->getDirection();
    for(auto &d : m_togglerDirections)
    {
        if(d == dir)
        {
            m_isEnabled = !m_isEnabled;
            return true;
        }
    }
    return false;
}