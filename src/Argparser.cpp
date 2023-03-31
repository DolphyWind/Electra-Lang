#include <Argparser.hpp>

Argparser::Argparser(int argc, char* argv[])
{
    if(argc == 1) return;
    for(int i = 1; i < argc; i++)
    {
        m_argsEntered.push_back(std::string(argv[i]));
    }
}

void Argparser::addArgument(const std::string &name, const std::string &shortName, bool store_boolean, const std::string &argumentDesc)
{
    m_args.push_back({name, shortName, store_boolean, argumentDesc});
}

std::tuple<std::unordered_map<std::string, std::string>, std::unordered_map<std::string, bool>> Argparser::parse()
{
    std::unordered_map<std::string, std::string> string_map;
    std::unordered_map<std::string, bool> bool_map;

    for(auto &arg : m_args)
    {
        std::string arg_name = arg.name;
        while(arg_name[0] == '-') arg_name.erase(0, 1);

        if(arg.store_boolean) bool_map[arg_name] = false;
        else string_map[arg_name] = std::string();
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
                while(a_name[0] == '-') a_name.erase(0, 1);

                if(a.store_boolean)
                {
                    bool_map[a_name] = true;
                }
                else
                {
                    if(i == m_argsEntered.size() - 1) break;
                    
                    std::string candidate = m_argsEntered[i + 1];
                    if(candidate[0] == '-') break;
                    string_map[a_name] = candidate;
                    defaultLogger.log(LogType::INFO, "Argument \"" + a_name + "\" is set to \"" + candidate + "\".");
                    ++i;
                }
                break;
            }
        }
    }
    return {string_map, bool_map};
}

std::vector<std::string> Argparser::getAloneArguments()
{
    return m_aloneArguments;
}

void Argparser::printVersionMessage()
{
    std::cout << program_name << " v" << ELECTRA_VERSION_MAJOR << "." << ELECTRA_VERSION_MINOR << "." << ELECTRA_VERSION_PATCH << std::endl;
}

void Argparser::printHelpMessage()
{
    printVersionMessage();
    std::cout << std::endl << program_description << std::endl << std::endl;

    std::cout << "Usage: " << binary_name << " [OPTIONS] INPUT_FILE" << std::endl << std::endl;
    std::cout << "Options: " << std::endl;
    for(auto &i : m_args)
    {
        std::cout << "\t" << i.shortName << ", " << i.name;
        if(!i.store_boolean) std::cout << " <arg>";
        std::cout << "\t" << i.argumentDesc << std::endl;
    }
    std::cout << std::endl;
}
