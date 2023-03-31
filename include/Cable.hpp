#pragma once
#include <direction.hpp>
#include <Component.hpp>
#include <vector>
#include <Current.hpp>
#include <algorithm>
#include <optional>
#include <Logger.hpp>

class Cable : public Component
{
    
public:
    Cable(std::vector<Direction> directions) : Component(directions) {};
    ~Cable() {};
    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};