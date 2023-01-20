#pragma once
#include <iostream>
#include <direction.hpp>
#include <memory>

class Current
{
private:
    Direction m_direction;
    Position m_position = {0, 0};
    Position m_portalPosition = {-1, -1};
public:
    Current(Direction direction): m_direction(direction) {};
    Current(Direction direction, Position position): m_position(position), m_direction(direction) {};
    ~Current() {};
    
    inline void setDirection(Direction direction) {m_direction = direction;}
    inline Direction getDirection() {return m_direction;}
    inline void setPosition(Position position) {m_position = position;}
    inline Position getPosition() {return m_position;}
    inline void setLastUsedPortalPosition(Position position) {m_portalPosition = position;}
    inline Position getLastUsedPortalPosition() {return m_portalPosition;}
    void iterate();
};

typedef std::shared_ptr<Current> CurrentPtr;