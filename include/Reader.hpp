#pragma once
#include <Current.hpp>
#include <direction.hpp>
#include <Cable.hpp>

// Takes input from user and pushes it on top of the stack of the current.

class Reader : public Cable
{
private:
    bool m_getInputAsChar = false;
public:
    Reader(std::vector<Direction> directions, bool getInputAsChar): 
        Cable(directions), m_getInputAsChar(getInputAsChar)
    {}
    ~Reader() {}

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};