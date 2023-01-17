#pragma once
#include <Component.hpp>

class Portal : public Component
{
    std::vector<Position> m_allCopies;
public:
    Portal(std::vector<Position> allCopies):
        Component({Direction::EAST, Direction::NORTHEAST, Direction::NORTH, Direction::NORTHWEST, Direction::WEST, Direction::SOUTHWEST, Direction::SOUTH, Direction::SOUTHEAST}), m_allCopies(allCopies)
    {}
    ~Portal() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};