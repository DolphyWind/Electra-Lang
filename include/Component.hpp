#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <Current.hpp>
#include <stack>
#include <Global.hpp>
#include <Logger.hpp>

// Electrical components

class Component
{
protected:
    std::vector<Direction> m_directions;
public:
    Component(std::vector<Direction> directions): m_directions(directions) {};
    ~Component() {};
    virtual bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector);
};

typedef std::shared_ptr<Component> ComponentPtr;