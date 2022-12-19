#pragma once
#include <iostream>
#include <vector>
#include <Current.hpp>
#include <Component.hpp>
#include <Generator.hpp>
#include <Cable.hpp>
#include <memory>
#include <map>
#include <fstream>
#include <sstream>

class Electra
{
    // Maps some chars to corresponding components
    std::map<char, Component*> m_components;
    std::vector<GeneratorPtr> m_generators;

    std::string m_filename;
    std::vector<std::vector<char>> m_sourceCode;
    // std::vector<Component*> m_components;
public:
    Electra(const std::string& filename);
    ~Electra();

    void run();
    std::vector<std::string> split(const std::string& str, const std::string& delim);
    void readSourceCode();
};