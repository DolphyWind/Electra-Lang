#include "Generator.hpp"

Generator::~Generator()
{

}

void Generator::update(std::vector<CurrentPtr> *currentVector)
{
    if(m_directions.empty()) return;
    if(!isActive()) return;
    m_generatedOnce = true;
    m_currentTick ++;

    if(m_currentTick >= m_tickDelay)
    {
        m_currentTick = 0;
        Direction dir = m_directions[m_directionIndex];
        Position deltaPos = directionToPosition(dir);
        Position resultPos = {0, 0};
        resultPos.x = m_position.x + deltaPos.x;
        resultPos.y = m_position.y + deltaPos.y;

        currentVector->push_back(std::make_shared<Current>(dir, resultPos));

        m_directionIndex ++;
        if(m_directionIndex >= m_directions.size()) m_directionIndex = 0;
    }
}

bool Generator::isActive()
{
    if(!m_isEnabled) return false;
    if(m_tickDelay == 0) return !m_generatedOnce;
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