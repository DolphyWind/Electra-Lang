/**
MIT License

Copyright (c) 2023 Yunus Emre Aydın

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
#if __has_include(<filesystem>)
  #include <filesystem>
  namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
  #include <experimental/filesystem> 
  namespace fs = std::experimental::filesystem;
#else
  error "Missing the <filesystem> header."
#endif

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
    fs::path m_currentPath;
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

    /// @brief Recursively includes a file. 
    /// 
    /// @param currentPath Current folder of the file. Helps when including files from some other direction.
    /// @param filename File to include
    /// @param start The start index of the slice
    /// @param end The end index of the slice
    /// @return Contents of recursively inclusion
    std::vector<std::wstring> includeFile(fs::path currentPath, const std::string& filename, std::size_t start = 0, std::size_t end = std::wstring::npos);

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