#pragma once
#include <iostream>
#include <vector>
#include <Current.hpp>
#include <Component.hpp>
#include <Cable.hpp>
#include <memory>
#include <map>

class Electra
{
    std::map<char, Component*> m_components;
    // std::vector<Component*> m_components;
public:
    Electra();
    ~Electra();

    void run();
};