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
#include <Printer.hpp>
#include <stack>
#include <ArithmeticalUnit.hpp>
#include <cmath>
#include <ConstantAdder.hpp>
#include <Cloner.hpp>
#include <ConstantPusher.hpp>
#include <Swapper.hpp>
#include <ConditionalUnit.hpp>
#include <Key.hpp>
#include <Portal.hpp>
#include <Reverser.hpp>
#include <Eraser.hpp>
#include <Argparser.hpp>
#include <csignal>

typedef std::vector<Direction> GeneratorData;

class Electra
{
    // Maps some chars to corresponding components.
    std::map<wchar_t, std::unique_ptr<Component>> m_components;
    
    // First element of DirectionPair corresponds to m_directions, second element corresponds to m_togglerDirections
    std::map<wchar_t, GeneratorData> m_generatorDataMap;
    std::vector<wchar_t> m_generatorChars;
    std::vector<GeneratorPtr> m_generators;

    std::vector<CurrentPtr> m_currents;
    
    // Related to files
    std::string m_filename;
    std::vector<std::wstring> m_sourceCode;

    // Holds indexes of currents that are soon to be deleted.
    std::vector<std::size_t> m_deadCurrentIndexes;
    // Currents that are going to be created via components.
    std::vector<CurrentPtr> m_newCurrents;

    // Main stack that language will use
    std::stack<var_t> m_stack;

    // Portal map
    std::map<wchar_t, Position> m_portalMap;

    // Signal handling.
    static bool m_isRunning;
    static void sigHandler(int signal);
    
public:
    Electra(int argc, char* argv[]);
    ~Electra();

    void run();
    std::vector<std::string> split(const std::string& str, const std::string& delim);
    std::vector<std::wstring> split_wstr(const std::wstring& str, const std::wstring& delim);
    void readSourceCode();
    void createGenerators();
    void createPortals();
    void mainLoop();

    // Methods for mainLoop() method.

    void moveCurrents();
    void generateGenerators();
    void interpreteCurrents();
    void removeCurrents();
    void createCurrents();
};