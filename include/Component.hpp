#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <Current.hpp>

// Electrical components

class Component
{
private:
public:
    Component() {};
    ~Component() {};
    virtual bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) = 0;
};

typedef std::shared_ptr<Component> ComponentPtr;