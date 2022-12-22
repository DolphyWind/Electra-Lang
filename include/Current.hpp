#pragma once
#include <iostream>
#include <direction.hpp>
#include <memory>

class Current
{
private:
    Direction m_direction;
    Position m_position = {0, 0};
    bool m_isDestroyed = false;
public:
    Current(Direction direction): m_direction(direction) {};
    Current(Direction direction, Position position): m_position(position), m_direction(direction) {};
    ~Current() {};
    
    void setDirection(Direction direction);
    Direction getDirection() {return m_direction;}
    void setPosition(Position position);
    Position getPosition() {return m_position;}
    void iterate();
    inline bool setDestroyed(bool state) {m_isDestroyed = state;}
    inline bool getDestroyed() {return m_isDestroyed;}
};

typedef std::shared_ptr<Current> CurrentPtr;