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
#include <algorithm>
#include <Logger.hpp>

typedef std::pair<std::vector<Direction>, std::vector<Direction>> DirectionPair;

class Electra
{
    // Maps some chars to corresponding components.
    std::map<char, Component*> m_components;
    
    // First element of DirectionPair corresponds to m_directions, second element corresponds to m_togglerDirections
    std::map<char, DirectionPair> m_generatorDirectionMap;
    std::vector<char> m_generatorChars;
    std::vector<GeneratorPtr> m_generators;

    std::vector<CurrentPtr> m_currents;

    std::string m_filename;
    std::vector<std::string> m_sourceCode;

    // Logger
    Logger m_logger;
public:
    Electra(const std::string& filename);
    ~Electra();

    void run();
    std::vector<std::string> split(const std::string& str, const std::string& delim);
    void readSourceCode();
    void createGenerators();
    void mainLoop();
};