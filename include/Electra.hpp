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
#include <tuple>

typedef std::tuple<std::vector<Direction>> GeneratorData;

class Electra
{
    // Maps some chars to corresponding components.
    std::map<char, Component*> m_components;
    
    // First element of DirectionPair corresponds to m_directions, second element corresponds to m_togglerDirections
    std::map<char, GeneratorData> m_generatorDataMap;
    std::vector<char> m_generatorChars;
    std::vector<GeneratorPtr> m_generators;

    std::vector<CurrentPtr> m_currents;
    
    // Related to files
    std::string m_filename;
    std::vector<std::string> m_sourceCode;

    // Holds indexes of currents that are soon to be deleted.
    std::vector<std::size_t> m_deadCurrentIndexes;
    // Currents that are going to be created via components.
    std::vector<CurrentPtr> m_newCurrents;
    
public:
    Electra(const std::string& filename);
    ~Electra();

    void run();
    std::vector<std::string> split(const std::string& str, const std::string& delim);
    void readSourceCode();
    void createGenerators();
    void mainLoop();

    // Methods for mainLoop() method.

    void moveCurrents();
    void generateGenerators();
    void interpreteCurrents();
    void removeCurrents();
    void createCurrents();
};