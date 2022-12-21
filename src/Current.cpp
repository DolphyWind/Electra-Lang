#include "Current.hpp"

void Current::setDirection(Direction direction)
{
    m_direction = direction;
}

void Current::setPosition(Position position)
{
    m_position = position;
}

void Current::iterate()
{
    Position deltaPos = directionToPosition(m_direction);
    m_position.x += deltaPos.x;
    m_position.y += deltaPos.y;
}
