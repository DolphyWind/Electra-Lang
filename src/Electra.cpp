#include "Electra.hpp"
#define _VARIADIC_MAX INT_MAX

bool Electra::m_isRunning = true;

/*
Initializes components, generators etc.
Takes source code filename as parameter
*/
Electra::Electra(int argc, char* argv[])
{
    Argparser parser(argc, argv);
    parser.program_name = "Electra";
    parser.program_description = "Electra is an esolang where you code like an electrician.\n" \
    "Find more about electra at https://github.com/DolphyWind/Electra-Lang";

    parser.addArgument("-h", "--help", true, "Print this message and exit.");
    parser.addArgument("-v", "--version", true, "Print version and exit.");
    parser.addArgument("-l", "--log", true, "Enables logging. Electra logs each step of the program and saves it into a file.");

    auto parser_args = parser.parse();
    auto string_map = std::get<0>(parser_args);
    auto bool_map = std::get<1>(parser_args);
    auto alone_args = parser.getAloneArguments();

    if(bool_map["help"])
    {
        parser.printHelpMessage();
        std::exit(0);
    }

    if(bool_map["version"])
    {
        parser.printVersionMessage();
        std::exit(0);
    }
    
    if(alone_args.size() == 0)
    {
        parser.printHelpMessage();
        std::exit(1);
    }
    
    defaultLogger.loggingEnabled = bool_map["log"];
    m_filename = alone_args[0];

    // Initializes cables
    // m_components['-'] = new Cable({Direction::WEST, Direction::EAST}) );
    m_components['-'] = std::make_unique<Cable>(std::vector<Direction>{Direction::WEST, Direction::EAST}) ;
    m_components['|'] = std::make_unique<Cable>( std::vector<Direction>{Direction::NORTH, Direction::SOUTH} );
    m_components['/'] = std::make_unique<Cable>( std::vector<Direction>{Direction::SOUTHWEST, Direction::NORTHEAST} );
    m_components['\\'] = std::make_unique<Cable>( std::vector<Direction>{Direction::SOUTHEAST, Direction::NORTHWEST} );
    m_components['+'] = std::make_unique<Cable>( std::vector<Direction>{Direction::WEST, Direction::EAST, Direction::NORTH, Direction::SOUTH} );
    m_components['X'] = std::make_unique<Cable>( std::vector<Direction>{Direction::SOUTHEAST, Direction::SOUTHWEST, Direction::NORTHEAST, Direction::NORTHWEST} );
    m_components['*'] = std::make_unique<Cable>( std::vector<Direction>{Direction::EAST, Direction::NORTHEAST, Direction::NORTH, Direction::NORTHWEST, Direction::WEST, Direction::SOUTHWEST, Direction::SOUTH, Direction::SOUTHEAST} );
    // I ran out of good ascii characters :(
    m_components['{'] = std::make_unique<Cable>( std::vector<Direction>{Direction::EAST} );
    m_components['}'] = std::make_unique<Cable>( std::vector<Direction>{Direction::WEST} );
    m_components['U'] = std::make_unique<Cable>( std::vector<Direction>{Direction::NORTH} );
    m_components['n'] = std::make_unique<Cable>( std::vector<Direction>{Direction::SOUTH} );

    // Initializes Printers
    m_components['N'] = std::make_unique<Printer>( std::vector<Direction>{Direction::NORTHWEST, Direction::SOUTHEAST, Direction::EAST, Direction::WEST, Direction::NORTHEAST, Direction::SOUTHWEST}, &m_stack, false);
    m_components['P'] = std::make_unique<Printer>( std::vector<Direction>{Direction::NORTH, Direction::WEST, Direction::EAST, Direction::NORTHEAST, Direction::NORTHWEST, Direction::SOUTHWEST}, &m_stack, true);
    
    // Initializes Arithmatical Units
    m_components['A'] = std::make_unique<ArithmeticalUnit>( std::vector<Direction>{Direction::NORTH, Direction::SOUTHEAST, Direction::SOUTHWEST}, &m_stack, [](var_t x, var_t y){return x + y;} );
    m_components['S'] = std::make_unique<ArithmeticalUnit>( std::vector<Direction>{Direction::NORTH, Direction::SOUTH, Direction::SOUTHWEST, Direction::NORTHEAST}, &m_stack, [](var_t x, var_t y){return x - y;} );
    m_components['M'] = std::make_unique<ArithmeticalUnit>( std::vector<Direction>{Direction::NORTHEAST, Direction::SOUTHEAST, Direction::SOUTHWEST, Direction::NORTHWEST, Direction::EAST, Direction::WEST}, &m_stack, [](var_t x, var_t y){return x * y;} );
    m_components['Q'] = std::make_unique<ArithmeticalUnit>( std::vector<Direction>{Direction::NORTH, Direction::SOUTH, Direction::WEST, Direction::EAST, Direction::SOUTHEAST}, &m_stack, [](var_t x, var_t y){return x / y;} );
    m_components['%'] = std::make_unique<ArithmeticalUnit>( std::vector<Direction>{Direction::NORTHEAST, Direction::SOUTHWEST}, &m_stack, [](var_t x, var_t y){return std::fmod(x, y);} );

    // Initializes constant adders
    m_components['I'] = std::make_unique<ConstantAdder>( std::vector<Direction>{Direction::NORTH, Direction::SOUTH}, &m_stack, 1);
    m_components['D'] = std::make_unique<ConstantAdder>( std::vector<Direction>{Direction::WEST, Direction::EAST, Direction::SOUTHWEST, Direction::NORTHWEST, Direction::NORTH, Direction::SOUTH}, &m_stack, -1);
    
    // Initializes cloner
    m_components['#'] = std::make_unique<Cloner>( std::vector<Direction>{Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST}, &m_stack);

    // Initializes constant pushers
    m_components['O'] = std::make_unique<ConstantPusher>( std::vector<Direction>{Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST, Direction::SOUTHEAST, Direction::SOUTHWEST, Direction::NORTHEAST, Direction::NORTHWEST}, &m_stack, false, false, 0);
    m_components['@'] = std::make_unique<ConstantPusher>( std::vector<Direction>{Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST, Direction::NORTHEAST, Direction::NORTHWEST, Direction::SOUTHWEST}, &m_stack, true, false, 0);
    m_components['&'] = std::make_unique<ConstantPusher>( std::vector<Direction>{Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::SOUTHEAST, Direction::SOUTHWEST}, &m_stack, true, true, 0);

    // Initializes swapper
    m_components['$'] = std::make_unique<Swapper>( std::vector<Direction>{Direction::NORTH, Direction::SOUTH, Direction::SOUTHWEST, Direction::NORTHEAST}, &m_stack);

    // Initializes conditional units
    m_components['['] = std::make_unique<ConditionalUnit>( std::vector<Direction>{Direction::NORTH, Direction::SOUTH}, &m_stack, 0, false);
    m_components[']'] = std::make_unique<ConditionalUnit>( std::vector<Direction>{Direction::NORTH, Direction::SOUTH}, &m_stack, 0, true);

    // Initializes keys
    m_components['~'] = std::make_unique<Key>( std::vector<Direction>{Direction::WEST, Direction::EAST}, std::vector<Direction>{Direction::NORTH, Direction::SOUTH}, m_sourceCode, '-');
    m_components['!'] = std::make_unique<Key>( std::vector<Direction>{Direction::NORTH, Direction::SOUTH}, std::vector<Direction>{Direction::WEST, Direction::EAST}, m_sourceCode, '|');

    // Initializes Reverser
    m_components['R'] = std::make_unique<Reverser>( std::vector<Direction>{Direction::NORTH, Direction::NORTHWEST, Direction::WEST, Direction::SOUTHWEST, Direction::SOUTHEAST}, &m_stack );

    // Saves generator characters and their directions and toggler directions in a map
    m_generatorDataMap['>'] = {Direction::EAST};
    m_generatorDataMap['^'] = {Direction::NORTH};
    m_generatorDataMap['<'] = {Direction::WEST};
    m_generatorDataMap['v'] = {Direction::SOUTH};
    
    // Saves generator chars seperately
    for(auto &p : m_generatorDataMap)
        m_generatorChars.push_back(p.first);
    
    #ifdef SIGTERM
    signal(SIGTERM, &Electra::sigHandler);
    #endif
    #ifdef SIGINT
    signal(SIGINT, &Electra::sigHandler);
    #endif
    #ifdef SIGQUIT
        signal(SIGQUIT, &Electra::sigHandler);
    #endif
    #ifdef SIGKILL
    signal(SIGKILL, &Electra::sigHandler);
    #endif
    #ifdef SIGHUP
    signal(SIGHUP, &Electra::sigHandler);
    #endif
}

Electra::~Electra()
{
    m_components.clear();
    m_generators.clear();
}

// Parses source code, creates generators and runs the code
void Electra::run()
{
    readSourceCode();
    createGenerators();
    createPortals();
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
    for(std::size_t y = 0; y < m_sourceCode.size(); y++)
    {
        for(std::size_t x = 0; x < m_sourceCode[y].size(); x++)
        {
            char currentChar = m_sourceCode.at(y).at(x);
            
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
Creates portals.
*/
void Electra::createPortals()
{
    for(std::size_t y = 0; y < m_sourceCode.size(); y++)
    {
        for(std::size_t x = 0; x < m_sourceCode[y].size(); x++)
        {
            char currentChar = m_sourceCode.at(y).at(x);
            if(currentChar == ' ' || currentChar == '\n') continue;
            
            bool isGenerator = false;
            for(auto &c : m_generatorChars)
            {
                if(c == currentChar)
                {
                    isGenerator = true;
                    break;
                }
            }
            if(isGenerator) continue;
            try
            {
                m_components.at(currentChar);
            }
            catch(const std::exception& e)
            {
                if(m_portalMap.find(currentChar) == m_portalMap.end())
                {
                    m_portalMap[currentChar] = {(int)x, (int)y};
                }
            }
            
        }
    }

    for(auto &p : m_portalMap)
    {
        m_components[p.first] = std::make_unique<Portal>(p.second);
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
            defaultLogger.log(LogType::INFO, "Removing current at ({},{}) with direction {} (Y coordinate out of bounds)", {curPos.x, curPos.y, (int)cur->getDirection()});
            continue;
        }
        if(curPos.x < 0 || curPos.x >= m_sourceCode[curPos.y].size())
        {
            m_deadCurrentIndexes.push_back(i);
            defaultLogger.log(LogType::INFO, "Removing current at ({},{}) with direction {} (X coordinate out of bounds)", {curPos.x, curPos.y, (int)cur->getDirection()});
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
                defaultLogger.log(LogType::INFO, "Removing current at ({},{}) with direction {} (Component refused to work.)", {curPos.x, curPos.y, (int)cur->getDirection()});
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
                    defaultLogger.log(LogType::INFO, "Removing current at ({},{}) with direction {} (Current does not align with generator)", {curPos.x, curPos.y, (int)cur->getDirection()});
                }
            }
            else
            {
                m_deadCurrentIndexes.push_back(i);
                defaultLogger.log(LogType::INFO, "Removing current at ({},{}) with direction {} (Not a component nor generator.)", {curPos.x, curPos.y, (int)cur->getDirection()});
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
