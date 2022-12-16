#pragma once
#include <iostream>
#include <direction.hpp>
#include <memory>

struct Position
{
    int x = 0;
    int y = 0;
};

class Current
{
private:
    Direction m_direction;
    Position m_position = {0, 0};
public:
    Current(Direction direction): m_direction(direction) {};
    Current(Direction direction, Position position): m_position(position), m_direction(direction) {};
    ~Current() {};
    
    void setDirection(Direction direction);
    Direction getDirection() {return m_direction;}
    void setPosition(Position position);
    Position getPosition() {return m_position;}
    void iterate();
};

typedef std::shared_ptr<Current> CurrentPtr;