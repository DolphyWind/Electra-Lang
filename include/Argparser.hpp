#ifndef _ARGPARSER_HPP_
#define _ARGPARSER_HPP_

#define ELECTRA_VERSION_MAJOR 2
#define ELECTRA_VERSION_MINOR 0
#define ELECTRA_VERSION_PATCH 0

#include <string>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <Logger.hpp>

// Simple argument parser
class Argparser
{
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

public:
    Argparser(int argc, char *argv[]);
    
    std::wstring_view binary_name;
    std::wstring_view program_name;
    std::wstring_view program_description;
    void addArgument(const std::string &name, const std::string &shortName, bool store_boolean=false, const std::string &argumentDesc=std::string());
    std::tuple<std::unordered_map<std::string, std::string>, std::unordered_map<std::string, bool>> parse();
    std::vector<std::string> getAloneArguments();
    
    void printVersionMessage();
    void printHelpMessage();
};

#endif // !_ARGPARSER_HPP_