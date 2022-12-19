#pragma once
#include <direction.hpp>
#include <iostream>
#include <vector>
#include <Current.hpp>
#include <memory>

class Generator
{
private:
    std::uint32_t m_currentTick = 0;
    std::uint32_t m_directionIndex = 0;
    bool m_generatedOnce = false;
    Position m_position;
    bool m_isEnabled = true;
protected:
    // Generator generates a current every m_tickDelay ticks (or once if m_tickDelay is equals to 0) in one of these directions.
    std::vector<Direction> m_directions; 

    // A current that comes from those directions toggles a generator's behaviour.
    std::vector<Direction> m_togglerDirections;
    std::uint32_t m_tickDelay = 0;
public:
    Generator(std::vector<Direction> directions, Position position, std::vector<Direction> togglerDirections, bool enabled = true, std::uint32_t tickDelay = 0): m_directions(directions), m_position(position), m_togglerDirections(togglerDirections), m_isEnabled(enabled), m_tickDelay(tickDelay) {};
    ~Generator();
    bool isActive();
    inline void setEnabled(bool enabled) {m_isEnabled = enabled;}
    inline bool getEnabled() {return m_isEnabled;}

    void update(std::vector<CurrentPtr> *currentVector);
};

typedef std::shared_ptr<Generator> GeneratorPtr;