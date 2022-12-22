#pragma once
#include <direction.hpp>
#include <iostream>
#include <vector>
#include <Current.hpp>
#include <memory>

// Generates currents.
// Can be enabled or disabled with a current whose direction is in m_togglerDirections
class Generator
{
private:
    std::uint32_t m_directionIndex = 0;
    bool m_generatedOnce = false;
    bool m_workOnce = true;
    bool m_isEnabled = true;
    Position m_position;
    CurrentPtr m_child = nullptr;
protected:
    // Generator generates a current every m_tickDelay ticks (or once if m_tickDelay is equals to 0) in one of these directions.
    std::vector<Direction> m_directions; 

    // A current that comes from those directions toggles m_isEnabled.
    std::vector<Direction> m_togglerDirections;
public:
    Generator(std::vector<Direction> directions, Position position, std::vector<Direction> togglerDirections = {}, bool enabled = true, bool workOnce = true): m_directions(directions), m_position(position), m_togglerDirections(togglerDirections), m_isEnabled(enabled), m_workOnce(workOnce) {};
    ~Generator();
    
    bool isActive();
    inline void setEnabled(bool enabled) {m_isEnabled = enabled;}
    inline bool getEnabled() {return m_isEnabled;}
    void update(std::vector<CurrentPtr> *currentVector);
    bool checkToggle(CurrentPtr current);
};

typedef std::shared_ptr<Generator> GeneratorPtr;