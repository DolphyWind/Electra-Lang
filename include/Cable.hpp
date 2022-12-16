#pragma once
#include <direction.hpp>
#include <Component.hpp>
#include <vector>
#include <Current.hpp>
#include <algorithm>

class Cable : public Component
{
    std::vector<Direction> m_directions;
public:
    Cable(std::vector<Direction> directions) : Component(), m_directions(directions) {};
    ~Cable();
    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};