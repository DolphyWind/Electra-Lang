#include "Electra.hpp"


Electra::Electra(const std::string& filename)
{
    m_components['-'] = new Cable( {Direction::WEST, Direction::EAST} );
    m_components['|'] = new Cable( {Direction::NORTH, Direction::SOUTH} );
    // m_components['/'] = new Cable( {Direction::SOUTHWEST, Direction::NORTHEAST} );
    // m_components['\\'] = new Cable( {Direction::SOUTHEAST, Direction::NORTHWEST} );
    m_components['+'] = new Cable( {Direction::WEST, Direction::EAST, Direction::NORTH, Direction::SOUTH} );
    // m_components['X'] = new Cable( {Direction::SOUTHEAST, Direction::SOUTHWEST, Direction::NORTHEAST, Direction::NORTHWEST} );

    m_filename = filename;
}

Electra::~Electra()
{
    for(auto& p : m_components)
    {
        delete p.second;
    }
    m_components.clear();
}

void Electra::run()
{
    readSourceCode();
    
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
            std::cout << "ERROR: Source code contains tab!" << std::endl;
            file.close();
            std::exit(1);
        }

        std::vector lines = split(fileData, "\n");
        std::size_t height = lines.size();
        std::size_t width = 0;
        for(auto &s : lines)
        {
            if(s.length() > width) width = s.length();
        }
        
        m_sourceCode = std::vector<std::vector<char>>(lines.size(), std::vector<char>(width, ' '));

        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < lines[i].length(); j++)
            {
                m_sourceCode[i][j] = lines[i][j];
            }
        }
    }
    else
    {
        std::cerr << "Cannot open \"" << m_filename << "\"" << std::endl;
        std::exit(1);
    }

    file.close();
}

