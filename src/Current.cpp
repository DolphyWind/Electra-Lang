#include <Current.hpp>

void Current::iterate()
{
    m_position = m_position + directionToPosition(m_direction);
}

void Current::addVisitedPortal(Position position)
{
    m_visitedPortalStack.push(position);
}

std::optional<Position> Current::popLastPortal()
{
    if(m_visitedPortalStack.empty()) return std::nullopt;
    
    Position top = m_visitedPortalStack.top();
    m_visitedPortalStack.pop();
    return top;
}
