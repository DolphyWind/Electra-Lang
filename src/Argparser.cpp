#include <Argparser.hpp>
#include <codecvt>
#include <locale>

Argparser::Argparser(int argc, char* argv[])
{
    if(argc == 1) return;
    for(int i = 1; i < argc; i++)
    {
        std::wstring_convert<std::codecvt_utf8<char_t>, char_t> converter;
        m_argsEntered.push_back( converter.from_bytes(argv[i]) );
    }
}

void Argparser::addArgument(const std::wstring &name, const std::wstring &shortName, bool store_boolean, const std::wstring &argumentDesc)
{
    m_args.push_back({shortName, name, store_boolean, argumentDesc});
}

std::tuple<std::unordered_map<std::wstring, std::wstring>, std::unordered_map<std::wstring, bool>> Argparser::parse()
{
    std::unordered_map<std::wstring, std::wstring> string_map;
    std::unordered_map<std::wstring, bool> bool_map;

    for(auto &arg : m_args)
    {
        std::wstring arg_name = arg.name;
        while(arg_name[0] == '-') arg_name.erase(0, 1);

        if(arg.store_boolean) bool_map[arg_name] = false;
        else string_map[arg_name] = std::wstring();
    }

    for(std::size_t i = 0; i < m_argsEntered.size(); ++i)
    {
        if(m_argsEntered[i][0] != L'-')
        {
            m_aloneArguments.push_back(m_argsEntered[i]);
            continue;
        }

        for(auto &a : m_args)
        {
            if(a.name == m_argsEntered[i] || a.shortName == m_argsEntered[i])
            {
                std::wstring a_name = a.name;
                while(a_name[0] == L'-') a_name.erase(0, 1);

                if(a.store_boolean)
                {
                    bool_map[a_name] = true;
                }
                else
                {
                    if(i == m_argsEntered.size() - 1) break;
                    
                    std::wstring candidate = m_argsEntered[i + 1];
                    if(candidate[0] == L'-') break;
                    string_map[a_name] = candidate;
                    ++i;
                }
                break;
            }
        }
    }
    return {string_map, bool_map};
}

std::vector<std::wstring> Argparser::getAloneArguments()
{
    return m_aloneArguments;
}

void Argparser::printVersionMessage()
{
    std::wcout << program_name << L" v" << ELECTRA_VERSION_MAJOR << L"." << ELECTRA_VERSION_MINOR << L"." << ELECTRA_VERSION_PATCH << std::endl;
}

void Argparser::printHelpMessage()
{
    printVersionMessage();
    std::size_t longest_argument_name_length = 0;
    for(auto &i : m_args)
    {
        std::size_t current_argument_message_length = i.shortName.length() + i.name.length();
        if(!i.store_boolean) current_argument_message_length += 6; // The length of " <arg>"
        if(current_argument_message_length > longest_argument_name_length) longest_argument_name_length = current_argument_message_length;
    }

    std::wcout << std::endl << program_description << std::endl << std::endl;

    std::wcout << L"Usage: " << binary_name << L" [OPTIONS] INPUT_FILE" << std::endl << std::endl;
    std::wcout << L"Options: " << std::endl;
    for(auto &i : m_args)
    {
        std::size_t argument_message_length = i.shortName.length() + i.name.length();
        std::wcout << L"\t" << i.shortName << L", " << i.name;
        if(!i.store_boolean) std::wcout << L" <arg>";
        std::wcout << std::wstring(longest_argument_name_length - argument_message_length, L' ') << L"\t" << i.argumentDesc << std::endl;
    }
    std::wcout << std::endl;
}
