#pragma once
#include <Cable.hpp>
#include <iostream>
#include <stack>
#include <direction.hpp>

class Printer : public Cable
{
private:
    std::stack<std::uint32_t> *m_stackPtr;
    bool m_printAsAscii = false;
public:
    Printer(std::vector<Direction> directions, std::stack<std::uint32_t> *stackPtr, bool printAsAscii):
        Cable(directions), m_stackPtr(stackPtr), m_printAsAscii(printAsAscii)
    {

    };
    ~Printer() {};

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};