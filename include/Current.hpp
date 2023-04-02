#pragma once
#include <iostream>
#include <direction.hpp>
#include <Global.hpp>
#include <memory>
#include <stack>
#include <optional>

class Current
{
private:
    Direction m_direction;
    Position m_position = {0, 0};
    std::stack<Position> m_visitedPortalStack;
    
public:
    Current(Direction direction): m_direction(direction) {};
    Current(Direction direction, Position position, StackPtr stackPtr): m_position(position), m_direction(direction), stackPtr(stackPtr) {};
    ~Current() {};
    
    inline void setDirection(Direction direction) {m_direction = direction;}
    inline Direction getDirection() {return m_direction;}
    inline void setPosition(Position position) {m_position = position;}
    inline Position getPosition() {return m_position;}
    void addVisitedPortal(Position position);
    std::optional<Position> popLastPortal();
    inline void setPortalStack(const std::stack<Position>& stack) {m_visitedPortalStack = stack;}
    inline std::stack<Position> getPortalStack() {return m_visitedPortalStack;};
    void iterate();

    StackPtr stackPtr;
};

typedef std::shared_ptr<Current> CurrentPtr;