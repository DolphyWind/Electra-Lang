#pragma once
#include <direction.hpp>
#include <iostream>
#include <vector>
#include <Current.hpp>
#include <memory>
#include <Logger.hpp>

// Generates currents.
class Generator
{
private:
    /// @brief Holds position value
    Position m_position;
    
    /// @brief Generator generates current from these directions.
    std::vector<Direction> m_directions; 
public:
    Generator(std::vector<Direction> directions, Position position): m_directions(directions), m_position(position) {};
    ~Generator() {};

    /// @brief Generates new current if it can
    /// @param currentVector Pushes the new current in this vector
    void generate(std::vector<CurrentPtr> *currentVector);

    std::vector<Direction> getDirections();
};

typedef std::shared_ptr<Generator> GeneratorPtr;