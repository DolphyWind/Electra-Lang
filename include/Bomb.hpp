#pragma once
#include <Cable.hpp>
#include <direction.hpp>

// Ends the program
class Bomb : public Cable
{
private:
    bool* m_isRunningPtr;
public:
    Bomb(std::vector<Direction> directions, bool* isRunningPtr):
        Cable(directions), m_isRunningPtr(isRunningPtr)
    {

    }
    ~Bomb() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};