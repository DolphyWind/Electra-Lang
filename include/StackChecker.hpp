#pragma once
#include <Current.hpp>
#include <direction.hpp>
#include <Cable.hpp>

// Checks if the stack is empty or not.
class StackChecker : public Cable
{
private:
    bool m_returnIfEmpty = false;
public:
    StackChecker(std::vector<Direction> directions, bool returnIfEmpty):
        Cable(directions), m_returnIfEmpty(returnIfEmpty)
    {}
    ~StackChecker() {}

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};