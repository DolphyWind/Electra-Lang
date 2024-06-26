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

#include <iostream>

#include <utility/ArgParser.hpp>


ArgParser::ArgParser(const std::vector<std::string>& args):
    m_argsEntered(args)
{
    m_argsEntered.erase(m_argsEntered.begin());
}

void ArgParser::addArgument(const std::string &name, const std::string &shortName, bool store_boolean, const std::string &argumentDesc)
{
    m_args.push_back({shortName, name, store_boolean, argumentDesc});
}

std::tuple<std::unordered_map<std::string, std::string>, std::unordered_map<std::string, bool>> ArgParser::parse()
{
    std::unordered_map<std::string, std::string> string_map;
    std::unordered_map<std::string, bool> bool_map;

    for(auto &arg : m_args)
    {
        std::string arg_name = arg.name;
        while(arg_name[0] == '-')
        {
            arg_name.erase(0, 1);
        }

        if(arg.store_boolean)
        {
            bool_map[arg_name] = false;
        }
        else
        {
            string_map[arg_name] = std::string();
        }
    }

    for(std::size_t i = 0; i < m_argsEntered.size(); ++i)
    {
        if(m_argsEntered[i][0] != '-')
        {
            m_aloneArguments.push_back(m_argsEntered[i]);
            continue;
        }

        for(auto &a : m_args)
        {
            if(a.name == m_argsEntered[i] || a.shortName == m_argsEntered[i])
            {
                std::string a_name = a.name;
                while(a_name[0] == '-')
                {
                    a_name.erase(0, 1);
                }

                if(a.store_boolean)
                {
                    bool_map[a_name] = true;
                }
                else
                {
                    if(i == m_argsEntered.size() - 1)
                    {
                        break;
                    }
                    
                    std::string candidate = m_argsEntered[i + 1];
                    for(auto &arg : m_args)
                    {
                        if(arg.name == candidate || arg.shortName == candidate)
                        {
                            break;
                        }
                    }
                    string_map[a_name] = candidate;
                    ++i;
                }
                break;
            }
        }
    }

    return {string_map, bool_map};
}

std::vector<std::string> ArgParser::getAloneArguments()
{
    return m_aloneArguments;
}

void ArgParser::printVersionMessage() const
{
    std::cout << program_name << " v" << ELECTRA_VERSION_MAJOR << '.' << ELECTRA_VERSION_MINOR << '.' << ELECTRA_VERSION_PATCH << std::endl;
}

void ArgParser::printHelpMessage()
{
    printVersionMessage();
    std::size_t longest_argument_name_length = 0;
    for(auto &i : m_args)
    {
        std::size_t current_argument_message_length = i.shortName.length() + i.name.length();
        if(!i.store_boolean)
        {
            current_argument_message_length += 6; // The length of " <arg>"
        }
        if(current_argument_message_length > longest_argument_name_length)
        {
            longest_argument_name_length = current_argument_message_length;
        }
    }

    std::cout << '\n' << program_description << "\n\n";

    std::cout << "Usage: " << binary_name << " [OPTIONS] INPUT_FILE\n\n";
    std::cout << "Options: \n";
    for(auto &i : m_args)
    {
        std::size_t argument_message_length = i.shortName.length() + i.name.length();
        std::cout << '\t' << i.shortName << ", " << i.name;
        if(!i.store_boolean)
        {
            std::cout << " <arg>";
        }
        std::cout << std::string(longest_argument_name_length - argument_message_length, ' ') << '\t' << i.argumentDesc << '\n';
    }
    std::cout << std::endl;
}
