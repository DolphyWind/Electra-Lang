#include "Electra.hpp"
#define _VARIADIC_MAX INT_MAX

bool Electra::m_isRunning = true;

/*
Initializes components, generators etc.
Takes source code filename as parameter
*/
Electra::Electra(const std::string& filename): m_filename(filename)
{
    // Initializes cables
    // I'll add unicode characters as cables in the future
    // I am not sure about Windows compatability though
    m_components['-'] = new Cable( {Direction::WEST, Direction::EAST} );
    m_components['|'] = new Cable( {Direction::NORTH, Direction::SOUTH} );
    m_components['/'] = new Cable( {Direction::SOUTHWEST, Direction::NORTHEAST} );
    m_components['\\'] = new Cable( {Direction::SOUTHEAST, Direction::NORTHWEST} );
    m_components['+'] = new Cable( {Direction::WEST, Direction::EAST, Direction::NORTH, Direction::SOUTH} );
    m_components['X'] = new Cable( {Direction::SOUTHEAST, Direction::SOUTHWEST, Direction::NORTHEAST, Direction::NORTHWEST} );
    m_components['✱'] = new Cable( {Direction::EAST, Direction::NORTHEAST, Direction::NORTH, Direction::NORTHWEST, Direction::WEST, Direction::SOUTHWEST, Direction::SOUTH, Direction::SOUTHEAST} );
    m_components['*'] = new Cable( {Direction::EAST, Direction::NORTHEAST, Direction::NORTH, Direction::NORTHWEST, Direction::WEST, Direction::SOUTHWEST, Direction::SOUTH, Direction::SOUTHEAST} );
    
    // Initializes Printers
    m_components['N'] = new Printer( {Direction::NORTHWEST, Direction::SOUTHEAST, Direction::EAST, Direction::WEST, Direction::NORTHEAST, Direction::SOUTHWEST}, &m_stack, false);
    m_components['P'] = new Printer( {Direction::NORTH, Direction::WEST, Direction::EAST, Direction::NORTHEAST, Direction::NORTHWEST, Direction::SOUTHWEST}, &m_stack, true);
    
    // Initializes Arithmatical Units
    m_components['A'] = new ArithmeticalUnit( {Direction::NORTH, Direction::SOUTHEAST, Direction::SOUTHWEST}, &m_stack, [](var_t x, var_t y){return x + y;} );
    m_components['S'] = new ArithmeticalUnit( {Direction::NORTH, Direction::SOUTH, Direction::SOUTHWEST, Direction::NORTHEAST}, &m_stack, [](var_t x, var_t y){return x - y;} );
    m_components['M'] = new ArithmeticalUnit( {Direction::NORTHEAST, Direction::SOUTHEAST, Direction::SOUTHWEST, Direction::NORTHWEST, Direction::EAST, Direction::WEST}, &m_stack, [](var_t x, var_t y){return x * y;} );
    m_components['Q'] = new ArithmeticalUnit( {Direction::NORTH, Direction::SOUTH, Direction::WEST, Direction::EAST, Direction::SOUTHEAST}, &m_stack, [](var_t x, var_t y){return x / y;} );
    m_components['%'] = new ArithmeticalUnit( {Direction::NORTHEAST, Direction::SOUTHWEST}, &m_stack, [](var_t x, var_t y){return std::fmod(x, y);} );

    // Initializes constant adders
    m_components['I'] = new ConstantAdder( {Direction::NORTH, Direction::SOUTH}, &m_stack, 1);
    m_components['D'] = new ConstantAdder( {Direction::WEST, Direction::EAST, Direction::SOUTHWEST, Direction::NORTHWEST, Direction::NORTH, Direction::SOUTH}, &m_stack, -1);
    
    // Initializes cloner
    m_components['#'] = new Cloner( {Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST}, &m_stack);

    // Initializes constant pushers
    m_components['O'] = new ConstantPusher( {Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST, Direction::SOUTHEAST, Direction::SOUTHWEST, Direction::NORTHEAST, Direction::NORTHWEST}, &m_stack, false, false, 0);
    m_components['@'] = new ConstantPusher( {Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST, Direction::NORTHEAST, Direction::NORTHWEST, Direction::SOUTHWEST}, &m_stack, true, false, 0);
    m_components['&'] = new ConstantPusher( {Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::SOUTHEAST, Direction::SOUTHWEST}, &m_stack, true, true, 0);

    // Initializes swapper
    m_components['$'] = new Swapper( {Direction::NORTH, Direction::SOUTH, Direction::SOUTHWEST, Direction::NORTHEAST}, &m_stack);

    // Initializes conditional units
    m_components['['] = new ConditionalUnit( {Direction::NORTH, Direction::SOUTH}, &m_stack, 0, true);
    m_components[']'] = new ConditionalUnit( {Direction::NORTH, Direction::SOUTH}, &m_stack, 0, false);

    // Saves generator characters and their directions and toggler directions in a map
    m_generatorDataMap['>'] = {Direction::EAST};
    m_generatorDataMap['^'] = {Direction::NORTH};
    m_generatorDataMap['<'] = {Direction::WEST};
    m_generatorDataMap['v'] = {Direction::SOUTH};
    
    // Saves generator chars seperately
    for(auto &p : m_generatorDataMap)
        m_generatorChars.push_back(p.first);
    
    signal(SIGTERM, &Electra::sigHandler);
    signal(SIGINT, &Electra::sigHandler);
    signal(SIGQUIT, &Electra::sigHandler);
    signal(SIGKILL, &Electra::sigHandler);
    signal(SIGHUP, &Electra::sigHandler);
}

Electra::~Electra()
{
    for(auto& p : m_components)
        delete p.second;

    m_components.clear();
    m_generators.clear();
}

// Parses source code, creates generators and runs the code
void Electra::run()
{
    readSourceCode();
    createGenerators();
    mainLoop();
}

// Splits a string based on a given delimiter
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

/*
The part that runs source code.
First it generates new currents with generators
And then it briefly does these in order on every loop:
- Makes components work
- Moves existing currents
- Removes currents that should be removed
- Creates new currents (For multi-directioned components)
*/
void Electra::mainLoop()
{
    int tickCount = 0;
    generateGenerators();

    do
    {
        defaultLogger.log(LogType::INFO, "Tick: {}", {tickCount});
        
        interpreteCurrents();
        moveCurrents();
        removeCurrents();    
        createCurrents();

        tickCount ++;
    }while (!m_currents.empty() && Electra::m_isRunning);

    defaultLogger.log(LogType::INFO, "Program finished. Total ticks: {}", {tickCount});
}

// Reads source code and saves it into m_sourceCode
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

// Creates generators
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
                defaultLogger.log(LogType::ERROR, "Can\'t get character at ({},{}) in source code. Exiting.", {x, y});
                std::cerr << e.what() << std::endl;
                std::exit(1);
            }
            
            for(auto &c : m_generatorChars)
            {
                if(c == currentChar)
                {
                    GeneratorData* genData = &m_generatorDataMap[c];

                    m_generators.push_back( std::make_shared<Generator>( 
                        *genData,
                        Position(x, y)
                    ) );
                }
            }
        }
    }
}

/*
Updates generators.
Generators will generate new current if they can.
*/
void Electra::generateGenerators()
{
    for(auto &gen : m_generators)
        gen->generate(&m_currents);
}

/*
Makes currents go one step further
*/
void Electra::moveCurrents()
{
    for(auto &cur : m_currents)
        cur->iterate();
}

/*
Make components work and also decides what currents to remove and create.
*/
void Electra::interpreteCurrents()
{
    for(std::size_t i = 0; i < m_currents.size(); i++)
    {
        auto &cur = m_currents[i];
        Position curPos = cur->getPosition();

        // Out of bounds check
        if(curPos.y < 0 || curPos.y >= m_sourceCode.size())
        {
            m_deadCurrentIndexes.push_back(i);
            defaultLogger.log(LogType::INFO, "Removing current at ({},{}) with index {} (Y coordinate out of bounds)", {curPos.x, curPos.y, int(i)});
            continue;
        }
        if(curPos.x < 0 || curPos.x >= m_sourceCode[curPos.y].size())
        {
            m_deadCurrentIndexes.push_back(i);
            defaultLogger.log(LogType::INFO, "Removing current at ({},{}) with index {} (X coordinate out of bounds)", {curPos.x, curPos.y, int(i)});
            continue;
        }

        // Main part that determines functionality of the current
        char currentChar = m_sourceCode[curPos.y][curPos.x];
        try
        {
            // throws an error if currentChar is not a key of m_components
            auto &comp = m_components.at(currentChar);
            if(!comp->work(cur, &m_newCurrents))
            {
                m_deadCurrentIndexes.push_back(i);
                defaultLogger.log(LogType::INFO, "Removing current at ({},{}) with index {} (Component does not support current\'s direction.)", {curPos.x, curPos.y, int(i)});
            }
        }
        catch(const std::exception& e)
        {
            bool isGenerator = false;
            for(auto &c : m_generatorChars)
            {
                if(currentChar == c)
                {
                    isGenerator = true;
                    break;
                }
            }
            if(isGenerator)
            {
                bool isAlignedWithGenerator = false;
                std::vector<Direction> directions = m_generatorDataMap[currentChar];
                for(auto& dir : directions)
                {
                    if(dir == cur->getDirection() || invertDirection(dir) == cur->getDirection())
                    {
                        isAlignedWithGenerator = true;
                        break;
                    }
                }
                if(!isAlignedWithGenerator)
                {
                    m_deadCurrentIndexes.push_back(i);
                    defaultLogger.log(LogType::INFO, "Removing current at ({},{}) with index {} (Current does not align with generator)", {curPos.x, curPos.y, int(i)});
                }
            }
            else
            {
                m_deadCurrentIndexes.push_back(i);
                defaultLogger.log(LogType::INFO, "Removing current at ({},{}) with index {} (Not a component nor generator.)", {curPos.x, curPos.y, int(i)});
            }
        }
    }
}

// Removes currents
void Electra::removeCurrents()
{
    std::sort(m_deadCurrentIndexes.begin(), m_deadCurrentIndexes.end(), std::greater<>());
    for(auto &i : m_deadCurrentIndexes)
    {
        m_currents[i] = nullptr;
        m_currents.erase(m_currents.begin() + i);
    }
    m_deadCurrentIndexes.clear();
}

// Creates currents
void Electra::createCurrents()
{
    for(auto &cur : m_newCurrents)
    {
        Position curPos = cur->getPosition();
        defaultLogger.log(LogType::INFO, "Created new current at ({},{}) with direction {}", {curPos.x, curPos.y, (int)cur->getDirection()});
        m_currents.push_back(cur);
    }
    
    m_newCurrents.clear();

    defaultLogger.log(LogType::INFO, "Total current count: {}", {(int)m_currents.size()});
}

void Electra::sigHandler(int signal)
{
    Electra::m_isRunning = false;
}
