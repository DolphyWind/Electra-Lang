#pragma once
#include <Component.hpp>

class Portal : public Component
{
    Position m_originalPosition;
public:
    Portal(Position originalPosition):
        Component({Direction::EAST, Direction::NORTHEAST, Direction::NORTH, Direction::NORTHWEST, Direction::WEST, Direction::SOUTHWEST, Direction::SOUTH, Direction::SOUTHEAST}), m_originalPosition(originalPosition)
    {}
    ~Portal() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};