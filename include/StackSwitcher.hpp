#pragma once
#include <Current.hpp>
#include <direction.hpp>
#include <Cable.hpp>
#include <stack>
#include <vector>

// Moves current's stack pointer forwards or backwards

class StackSwitcher : public Cable
{
private:
    std::vector<std::stack<var_t>> *m_stacks;
    bool m_moveForward = true;
public:
    StackSwitcher(std::vector<Direction> directions, bool moveForward, std::vector<std::stack<var_t>> *stacks):
        Cable(directions), m_moveForward(moveForward), m_stacks(stacks)
    {}
    ~StackSwitcher() {}

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};