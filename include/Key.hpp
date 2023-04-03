#pragma once
#include <Cable.hpp>

class Key : public Cable
{
    std::vector<Direction> m_activatorDirections;
    std::vector<std::wstring> &m_sourceCode;
    char_t m_transformTo;
public:
    Key(std::vector<Direction> directions, std::vector<Direction> activatorDirections, std::vector<std::wstring> &sourceCode, char_t transformTo):
        Cable(directions), m_activatorDirections(activatorDirections), m_sourceCode(sourceCode), m_transformTo(transformTo)
    {}
    ~Key(){}

    bool work(CurrentPtr current, std::vector<CurrentPtr> *currentVector) override;
};