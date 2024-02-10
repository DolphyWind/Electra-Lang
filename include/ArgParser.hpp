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

#define ELECTRA_VERSION_MAJOR 2
#define ELECTRA_VERSION_MINOR 2
#define ELECTRA_VERSION_PATCH 0

#include <vector>
#include <unordered_map>

// Simple argument parser
// Parses arguments into three categories:
// Bool arguments: Arguments that store true if they are present
// String arguments: Arguments that store succeeding argument
// Alone arguments: Arguments that are not specified to store anything
class ArgParser
{
public:
    explicit ArgParser(const std::vector<std::string>& args);
    
    std::string_view binary_name;
    std::string_view program_name;
    std::string_view program_description;
    void addArgument(const std::string &name, const std::string &shortName, bool store_boolean=false, const std::string &argumentDesc=std::string());
    std::tuple<std::unordered_map<std::string, std::string>, std::unordered_map<std::string, bool>> parse();
    std::vector<std::string> getAloneArguments();
    
    void printVersionMessage() const;
    void printHelpMessage();

private:
    struct Argument
    {
        std::string shortName;
        std::string name;
        bool store_boolean;
        std::string argumentDesc;
    };

    std::vector<Argument> m_args;
    std::vector<std::string> m_argsEntered;
    std::vector<std::string> m_aloneArguments;
};
