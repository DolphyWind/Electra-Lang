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
        std::wstring shortName;
        std::wstring name;
        bool store_boolean;
        std::wstring argumentDesc;
    };
    
    std::vector<Argument> m_args;
    std::vector<std::wstring> m_argsEntered;
    std::vector<std::wstring> m_aloneArguments;

public:
    Argparser(int argc, char *argv[]);

    std::wstring_view binary_name;
    std::wstring_view program_name;
    std::wstring_view program_description;
    void addArgument(const std::wstring &name, const std::wstring &shortName, bool store_boolean=false, const std::wstring &argumentDesc=std::wstring());
    std::tuple<std::unordered_map<std::wstring, std::wstring>, std::unordered_map<std::wstring, bool>> parse();
    std::vector<std::wstring> getAloneArguments();
    
    void printVersionMessage();
    void printHelpMessage();
};

#endif // !_ARGPARSER_HPP_