#include "Generator.hpp"

void Generator::generate(std::vector<CurrentPtr> *currentVector)
{
    for(auto& dir : m_directions)
    {
        // Direction and position of the new current
        Position deltaPos = directionToPosition(dir);
        Position resultPos = m_position + deltaPos;

        currentVector->push_back(std::make_shared<Current>(dir, resultPos));
        defaultLogger.log(LogType::INFO, "Creating new current from a generator at ({},{})", {m_position.x, m_position.y});
    }
}

std::vector<Direction> Generator::getDirections()
{
    return m_directions;
}