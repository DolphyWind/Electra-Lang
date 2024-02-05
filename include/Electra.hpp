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
#include <stack>
#include <cmath>
#include <csignal>
#include <regex>
#include <stdexcept>
#include <cstring>
#include <set>
#if __has_include(<filesystem>)
  #include <filesystem>
  namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
  #include <experimental/filesystem> 
  namespace fs = std::experimental::filesystem;
#else
  #error "Missing the <filesystem> header."
#endif

#include <Logger.hpp>
#include <Printer.hpp>
#include <ArithmeticalUnit.hpp>
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
#include <string_utilities.hpp>
#include <LineRange.hpp>

typedef std::vector<Direction> GeneratorData;

class Electra
{
public:

    /// @brief Sets up components and generators.
    Electra();

    /// @brief Parses command line arguments, and sets up components and generators.
    explicit Electra(const std::vector<std::string>& args);

    ~Electra() = default;

    /// @brief Set the source code of the electra interpreter
    /// @param sourceCode New source code
    void setSourceCode(const std::string& sourceCode);

    /// @brief Load the source code of the electra interpreter from a file
    /// @param filepath Path of the file to load from
    void loadSourceFromFile(const std::string& filepath);

    /// @brief Main loop of electra
    /// Generates first set of currents before loop.
    /// During loop, it does these jobs in given order
    /// - Make components work and mark some of them to be removed
    /// - Move currents
    /// - Remove marked currents
    /// - Create new currents
    void mainLoop();

private:

    void setupComponentsAndGenerators();
    void setupSignalHandlers();

    /// @brief Cleans up some containers
    void cleanup();

//    /// @brief Loads a file
//    /// @param currentPath Location that the file belongs to. Helps when including files from some other direction.
//    /// @param filename File to load
//    std::vector<std::string> loadFile(fs::path currentPath, const std::string& filename);
//
//    /// @brief Recursively includes a file. Caution: Included file will have comments and will be reversed.
//    /// @param currentPath Location that the file belongs to. Helps when including files from some other direction.
//    /// @param filename File to include
//    /// @param lineRange Line range to include
//    /// @return Contents of recursively inclusion
//    std::vector<std::string> includeFile(fs::path currentPath, const std::string& filename, LineRange lineRange=LineRange{}, bool allow_reinclusion=false);

    /// @brief Creates generators from source code
    void createGenerators();

    /// @brief Creates portals from source code
    void createPortals();

    // Methods for mainLoop() method.
    void moveCurrents();
    void generateFromGenerators();
    void interpretCurrents();
    void removeCurrents();
    void createCurrents();

    // Maps some chars to corresponding components.
    std::unordered_map<char32_t, std::unique_ptr<Component>> m_components;

    // Generators and currents
    std::unordered_map<char32_t, GeneratorData> m_generatorDataMap;
    std::vector<char32_t> m_generatorChars;
    std::vector<GeneratorPtr> m_generators;
    std::vector<CurrentPtr> m_currents;

    // Related to files
    std::string m_filename;
    fs::path m_currentPath;
    std::vector<std::u32string> m_sourceCode;
    std::unordered_map<std::string, std::set<LineRange>> m_includedParts;

    // Holds indexes of currents that are soon to be deleted. Gets cleared every loop.
    std::vector<std::size_t> m_deadCurrentIndices;

    // Holds the list of Currents that are going to be created at the end of the loop. Components update this list.
    std::vector<CurrentPtr> m_newCurrents;

    // Memory management
    std::vector<std::stack<var_t>> m_stacks;
    static constexpr std::size_t default_stack_count = 64;

    // A map object that holds positions of original portals as its values
    std::unordered_map<char32_t, Position> m_portalMap;

    // Signal handling.
    static void sigHandler(int signal);
};