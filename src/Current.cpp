#include "Current.hpp"

void Current::iterate()
{
    m_position = m_position + directionToPosition(m_direction);
}
