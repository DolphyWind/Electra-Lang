#include "Electra.hpp"
#define _VARIADIC_MAX INT_MAX

Electra::Electra(const std::string& filename): m_filename(filename)
{
    m_components['-'] = new Cable( {Direction::WEST, Direction::EAST} );
    m_components['|'] = new Cable( {Direction::NORTH, Direction::SOUTH} );

    m_components['/'] = new Cable( {Direction::SOUTHWEST, Direction::NORTHEAST} );
    m_components['\\'] = new Cable( {Direction::SOUTHEAST, Direction::NORTHWEST} );

    m_components['+'] = new Cable( {Direction::WEST, Direction::EAST, Direction::NORTH, Direction::SOUTH} );
    m_components['X'] = new Cable( {Direction::SOUTHEAST, Direction::SOUTHWEST, Direction::NORTHEAST, Direction::NORTHWEST} );

    m_components['✱'] = new Cable( {Direction::EAST, Direction::NORTHEAST, Direction::NORTH, Direction::NORTHWEST, Direction::WEST, Direction::SOUTHWEST, Direction::SOUTH, Direction::SOUTHEAST} );
    m_components['*'] = new Cable( {Direction::EAST, Direction::NORTHEAST, Direction::NORTH, Direction::NORTHWEST, Direction::WEST, Direction::SOUTHWEST, Direction::SOUTH, Direction::SOUTHEAST} );


    m_generatorDirectionMap['>'] = {{Direction::EAST}, {}};
    m_generatorDirectionMap['^'] = {{Direction::NORTH}, {}};
    m_generatorDirectionMap['<'] = {{Direction::WEST}, {}};
    m_generatorDirectionMap['v'] = {{Direction::SOUTH}, {}};
    m_generatorDirectionMap['~'] = {{Direction::EAST, Direction::WEST}, {Direction::NORTH, Direction::SOUTH} };
    m_generatorDirectionMap['S'] = {{Direction::NORTH, Direction::SOUTH}, {Direction::EAST, Direction::WEST} };

    for(auto &p : m_generatorDirectionMap)
        m_generatorChars.push_back(p.first);
}

Electra::~Electra()
{
    for(auto& p : m_components)
        delete p.second;

    m_components.clear();
    m_generators.clear();
}

void Electra::run()
{
    readSourceCode();
    createGenerators();
}

std::vector<std::string> Electra::split(const std::string& str, const std::string& delim) 
{
    std::vector<std::string> tokens;
    std::size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if(pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

void Electra::readSourceCode()
{
    std::ifstream file(m_filename);

    if(file.good())
    {
        std::string fileData;
        std::stringstream ss;
        ss << file.rdbuf();
        fileData = ss.str();

        if(fileData.find('\t') != std::string::npos) 
        {
            std::cerr << "ERROR: Source code contains tab!" << std::endl;
            file.close();
            std::exit(1);
        }

        m_sourceCode = split(fileData, "\n");
    }
    else
    {
        std::cerr << "Cannot open \"" << m_filename << "\"" << std::endl;
        std::exit(1);
    }

    file.close();
}

void Electra::createGenerators()
{
    for(int y = 0; y < m_sourceCode.size(); y++)
    {
        for(int x = 0; x < m_sourceCode[y].size(); x++)
        {
            char currentChar;
            try
            {
                currentChar = m_sourceCode.at(y).at(x);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
                std::exit(1);
            }
            
            for(auto &c : m_generatorChars)
            {
                if(c == currentChar)
                {
                    m_generators.push_back( std::make_shared<Generator>( 
                        m_generatorDirectionMap[c].first,
                        Position(x, y),
                        m_generatorDirectionMap[c].second,
                        true,
                        0
                    ) );
                }
            }
        }
    }
}

