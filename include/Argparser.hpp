#ifndef _ARGPARSER_HPP_
#define _ARGPARSER_HPP_

#define ELECTRA_VERSION_MAJOR 1
#define ELECTRA_VERSION_MINOR 1
#define ELECTRA_VERSION_PATCH 0

#include <string>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <iostream>

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
    std::string_view m_binaryName;

public:
    Argparser(int argc, char *argv[]);

    std::string_view program_name;
    std::string_view program_description;
    void addArgument(const std::string &name, const std::string &shortName, bool store_boolean=false, const std::string &argumentDesc=std::string());
    std::tuple<std::unordered_map<std::string, std::string>, std::unordered_map<std::string, bool>> parse();
    std::vector<std::string> getAloneArguments();
    
    void printVersionMessage();
    void printHelpMessage();
};

#endif // !_ARGPARSER_HPP_