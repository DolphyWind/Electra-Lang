#pragma once
#include <iostream>
#include <vector>
#include <Current.hpp>
#include <Component.hpp>
#include <Generator.hpp>
#include <Cable.hpp>
#include <memory>
#include <unordered_map>
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
#include <Bomb.hpp>
#include <Reader.hpp>
#include <StackChecker.hpp>
#include <StackSwitcher.hpp>
#include <csignal>
#include <regex>
#include <codecvt>
#include <stdexcept>

typedef std::vector<Direction> GeneratorData;

class Electra
{
    // Maps some chars to corresponding components.
    std::unordered_map<char_t, std::unique_ptr<Component>> m_components;
    
    // Variables for generators and currents
    std::unordered_map<char_t, GeneratorData> m_generatorDataMap;
    std::vector<char_t> m_generatorChars;
    std::vector<GeneratorPtr> m_generators;
    std::vector<CurrentPtr> m_currents;
    
    // Related to files
    std::string m_filename;
    std::vector<std::wstring> m_sourceCode;

    // Holds indexes of currents that are soon to be deleted. Gets cleared every loop.
    std::vector<std::size_t> m_deadCurrentIndexes;
    
    // Currents that are going to be created via components.
    std::vector<CurrentPtr> m_newCurrents;

    // Stacks that language will use for memory manager
    std::vector<std::stack<var_t>> m_stacks;
    const std::size_t default_stack_count = 16;

    // A map object that holds portals
    std::unordered_map<char_t, Position> m_portalMap;

    // Signal handling.
    static bool m_isRunning;
    static void sigHandler(int signal);
    
public:
    /// @brief Parses command line arguments, and initializes component and generators.
    /// 
    /// @param argc Command line argument count
    /// @param argv Command line arguments
    Electra(int argc, char* argv[]);

    /// @brief Clears components and generators
    ~Electra();

    /// @brief 
    /// 
    void run();

    /// @brief Splits a string based on a given delimiter
    /// 
    /// @param str String to split
    /// @param delim Delimeter
    /// @return Splitted string
    std::vector<std::string> split(const std::string& str, const std::string& delim);

    /// @brief Splits a wstring based on a given delimeter
    /// 
    /// @param str Wstring to split
    /// @param delim Delimeter
    /// @return Splitted wstring
    std::vector<std::wstring> split_wstr(const std::wstring& str, const std::wstring& delim);

    /// @brief Reads the source code into m_sourceCode
    void readSourceCode();

    /// @brief Removes comments from the source code.
    void removeComments();

    /// @brief Creates generators from source code
    void createGenerators();

    /// @brief Creates portals from source code
    void createPortals();

    /// @brief Main loop of electra
    /// Generates first set of currents before loop.
    /// During loop, it does these jobs in given order
    /// - Make components work and mark some of them to be removed
    /// - Move currents
    /// - Remove marked currents
    /// - Create new currents
    void mainLoop();

    // Methods for mainLoop() method.
    void moveCurrents();
    void generateGenerators();
    void interpreteCurrents();
    void removeCurrents();
    void createCurrents();
};