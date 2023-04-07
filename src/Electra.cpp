#include "StackChecker.hpp"
#include "StackSwitcher.hpp"
#include "direction.hpp"
#include <Electra.hpp>
#include <Logger.hpp>
#include <codecvt>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
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
    parser.binary_name = "electra";
    parser.program_description = "Electra is an esolang where you code like an electrician.\n" \
    "Find more about electra at https://github.com/DolphyWind/Electra-Lang";

    parser.addArgument("--help", "-h", true, "Print this message and exit.");
    parser.addArgument("--version", "-v", true, "Print version and exit.");
    parser.addArgument("--log", "-l", true, "Enables logging. Electra logs each step of the program and saves it into a file.");
    parser.addArgument("--stack", "-s", false, "Specify the inital values of stack.");
    parser.addArgument("--stack-count", "-sc", false, "Specify the total stack count that electra uses. Must be greater than or equal to one.");

    auto parser_args = parser.parse();
    auto string_map = std::get<0>(parser_args);
    auto bool_map = std::get<1>(parser_args);
    auto alone_args = parser.getAloneArguments();

    defaultLogger.loggingEnabled = bool_map["log"];

    if(bool_map["help"])
    {
        parser.printHelpMessage();
        defaultLogger.log(LogType::INFO, L"Printed help message. Exiting with code 0.");
        std::exit(0);
    }

    if(bool_map["version"])
    {
        parser.printVersionMessage();
        defaultLogger.log(LogType::INFO, L"Printed current version of electra. Exiting with code 0.");
        std::exit(0);
    }
    
    if(alone_args.size() == 0)
    {
        parser.printHelpMessage();
        defaultLogger.log(LogType::INFO, L"No arguments specified. Printing help message. Exiting with code 1.");
        std::exit(1);
    }

    std::string stack_count_str = string_map["stack-count"];
    std::size_t stack_count = 0;
    
    try
    {
        if(stack_count_str.empty()) stack_count = Electra::default_stack_count;
        else stack_count = std::stoi(stack_count_str);
        if(stack_count == 0) throw std::invalid_argument("Stack count should be greater than zero!");
        
        for(std::size_t i = 0; i < stack_count; i++)
        {
            m_stacks.push_back({});
        }
    }
    catch (const std::invalid_argument &e)
    {
        defaultLogger.log(LogType::ERROR, L"\"{}\" is invalid for stack-count.\n");
        std::cerr << '\"' << stack_count_str << "\" is invalid for stack-count.\n";
        std::exit(1);
    }
    catch (const std::out_of_range &e)
    {
        defaultLogger.log(LogType::ERROR, L"\"{}\" is out of range for stack-count.", stack_count_str);
        std::cerr << '\"' << stack_count_str << "\" is out of range for stack-count." << std::endl;
        std::exit(1);
    }
    std::size_t index = 0;
    for(auto &splitted : this->split(string_map["stack"], ","))
    {
        for(auto &i : this->split(splitted, " "))
        {
            if(i.empty()) continue;

            try
            {
                m_stacks[index].push(std::stod(i));
            }
            catch(const std::out_of_range &e)
            {
                defaultLogger.log(LogType::ERROR, L"The value {} is too big or small for var_t.", i);
                std::cerr << "The value " << i << " is too big or small for var_t." << std::endl;
                std::exit(1);
            }
            catch(const std::invalid_argument &e)
            {
                defaultLogger.log(LogType::ERROR, L"Can\'t convert {} to var_t.", i);
                std::cerr << "Can\'t convert " << i << " to var_t." << std::endl;
                std::exit(1);
            }
        }
        index ++;
    }
    
    m_filename = alone_args[0];

    // Initializes cables
    // m_components['-'] = new Cable({Direction::WEST, Direction::EAST}) );
    m_components[L'-'] = std::make_unique<Cable>( bin2dir(0b00010001) );
    m_components[L'⎯'] = std::make_unique<Cable>( bin2dir(0b00010001) );
    
    m_components[L'|'] = std::make_unique<Cable>( bin2dir(0b01000100) );
    
    m_components[L'/'] = std::make_unique<Cable>( bin2dir(0b00100010) );
    m_components[L'╱'] = std::make_unique<Cable>( bin2dir(0b00100010) );
    
    m_components[L'\\'] = std::make_unique<Cable>( bin2dir(0b10001000) );
    m_components[L'╲'] = std::make_unique<Cable>( bin2dir(0b10001000) );
    
    m_components[L'+'] = std::make_unique<Cable>( bin2dir(0b01010101) );
    m_components[L'┼'] = std::make_unique<Cable>( bin2dir(0b01010101) );
    
    m_components[L'X'] = std::make_unique<Cable>( bin2dir(0b10101010) );
    m_components[L'╳'] = std::make_unique<Cable>( bin2dir(0b10101010) );
    
    m_components[L'*'] = std::make_unique<Cable>( bin2dir(0b11111111) );
    m_components[L'✱'] = std::make_unique<Cable>( bin2dir(0b11111111) );

    m_components[L'╰'] = std::make_unique<Cable>( bin2dir(0b00000101) );
    m_components[L'└'] = std::make_unique<Cable>( bin2dir(0b00000101) );

    m_components[L'╯'] = std::make_unique<Cable>( bin2dir(0b00010100) );
    m_components[L'┘'] = std::make_unique<Cable>( bin2dir(0b00010100) );

    m_components[L'╭'] = std::make_unique<Cable>( bin2dir(0b01000001) );
    m_components[L'┌'] = std::make_unique<Cable>( bin2dir(0b01000001) );

    m_components[L'┐'] = std::make_unique<Cable>( bin2dir(0b01010000) );
    m_components[L'╮'] = std::make_unique<Cable>( bin2dir(0b01010000) );

    m_components[L'├'] = std::make_unique<Cable>( bin2dir(0b00010101) );
    m_components[L'┤'] = std::make_unique<Cable>( bin2dir(0b01010100) );
    m_components[L'┬'] = std::make_unique<Cable>( bin2dir(0b01010001) );
    m_components[L'┴'] = std::make_unique<Cable>( bin2dir(0b00010101) );

    // I ran out of good ascii characters :(
    m_components[L'{'] = std::make_unique<Cable>( bin2dir(0b00000001) );
    m_components[L'}'] = std::make_unique<Cable>( bin2dir(0b00010000) );
    m_components[L'U'] = std::make_unique<Cable>( bin2dir(0b00000100) );
    m_components[L'n'] = std::make_unique<Cable>( bin2dir(0b01000000) );
    
    // Initializes Printers
    m_components[L'N'] = std::make_unique<Printer>( bin2dir(0b10111011), false);
    m_components[L'P'] = std::make_unique<Printer>( bin2dir(0b00111111), true);
    
    // Initializes Arithmatical Units
    m_components[L'A'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b10100100), [](var_t x, var_t y){return x + y;} );
    m_components[L'S'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b01100110), [](var_t x, var_t y){return x - y;} );
    m_components[L'M'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b11111011), [](var_t x, var_t y){return x * y;} );
    m_components[L'Q'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b11010101), [](var_t x, var_t y){return x / y;} );
    m_components[L'%'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b00100010), [](var_t x, var_t y){return std::fmod(x, y);} );

    // Initializes constant adders
    m_components[L'I'] = std::make_unique<ConstantAdder>( bin2dir(0b01000100), 1);
    m_components[L'D'] = std::make_unique<ConstantAdder>( bin2dir(0b01111101), -1);
    
    // Initializes cloner
    m_components[L'#'] = std::make_unique<Cloner>( bin2dir(0b01010101) );

    // Initializes constant pusher
    m_components[L'O'] = std::make_unique<ConstantPusher>( bin2dir(0b11111111), 0);
    
    // Initializes readers
    m_components[L'@'] = std::make_unique<Reader>( bin2dir(0b01111111), false);
    m_components[L'&'] = std::make_unique<Reader>( bin2dir(0b11100101), true);

    // Initializes swapper
    m_components[L'$'] = std::make_unique<Swapper>( bin2dir(0b01100110) );

    // Initializes conditional units
    m_components[L'['] = std::make_unique<ConditionalUnit>( bin2dir(0b01000100), 0, false);
    m_components[L']'] = std::make_unique<ConditionalUnit>( bin2dir(0b01000100), 0, true);
    
    // Initializes stack checkers
    m_components[L'('] = std::make_unique<StackChecker>( bin2dir(0b01000100), true);
    m_components[L')'] = std::make_unique<StackChecker>( bin2dir(0b01000100), false);

    // Initializes stack switchers
    m_components[L'F'] = std::make_unique<StackSwitcher>( bin2dir(0b00111111), true, &m_stacks);
    m_components[L'B'] = std::make_unique<StackSwitcher>( bin2dir(0b11111110), false, &m_stacks);

    // Initializes keys
    m_components[L'~'] = std::make_unique<Key>( bin2dir(0b00010001), bin2dir(0b01000100), m_sourceCode, L'-');
    m_components[L'!'] = std::make_unique<Key>( bin2dir(0b01000100), bin2dir(0b00010001), m_sourceCode, L'|');
    
    // Initializes Reverser
    m_components[L'R'] = std::make_unique<Reverser>( bin2dir(0b10111111) );
    
    // Initializes Remover
    m_components[L'E'] = std::make_unique<Eraser>( bin2dir(0b11111111) );

    // Initializes Bomb
    m_components[L'o'] = std::make_unique<Bomb>( bin2dir(0b11111111), &m_isRunning );

    // Saves generator characters and their directions and toggler directions in a map
    m_generatorDataMap[L'>'] = bin2dir(0b00000001);
    m_generatorDataMap[L'→'] = bin2dir(0b00000001);

    m_generatorDataMap[L'^'] = bin2dir(0b00000100);
    m_generatorDataMap[L'↑'] = bin2dir(0b00000100);
    
    m_generatorDataMap[L'<'] = bin2dir(0b00010000);
    m_generatorDataMap[L'←'] = bin2dir(0b00010000);
    
    m_generatorDataMap[L'v'] = bin2dir(0b01000000);
    m_generatorDataMap[L'↓'] = bin2dir(0b01000000);
    
    m_generatorDataMap[L'↔'] = bin2dir(0b00010001);
    m_generatorDataMap[L'↕'] = bin2dir(0b01000100);
    m_generatorDataMap[L'↗'] = bin2dir(0b00000010);
    m_generatorDataMap[L'↖'] = bin2dir(0b00001000);
    m_generatorDataMap[L'↙'] = bin2dir(0b00100000);
    m_generatorDataMap[L'↘'] = bin2dir(0b10000000);
    
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

std::vector<std::wstring> Electra::split_wstr(const std::wstring& str, const std::wstring& delim)
{
    std::vector<std::wstring> tokens;
    std::size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if(pos == std::string::npos) pos = str.length();
        std::wstring token = str.substr(prev, pos-prev);
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
    defaultLogger.log(LogType::INFO, L"Program started!");
    int tickCount = 0;
    generateGenerators();

    do
    {
        defaultLogger.log(LogType::INFO, L"Tick: {}", tickCount);
        
        interpreteCurrents();
        moveCurrents();
        removeCurrents();    
        createCurrents();

        tickCount ++;
    }while (!m_currents.empty() && Electra::m_isRunning);

    defaultLogger.log(LogType::INFO, L"Program finished. Total ticks: {}", tickCount);
}

// Reads source code and saves it into m_sourceCode
void Electra::readSourceCode()
{
    defaultLogger.log(LogType::INFO, L"Started reading source code to memory!");
    std::wifstream file(m_filename);
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<char_t>));

    if(file.good())
    {
        std::wstring fileData;
        std::wstringstream ss;
        ss << file.rdbuf();
        fileData = ss.str();

        if(fileData.find('\t') != std::string::npos) 
        {
            defaultLogger.log(LogType::ERROR, L"Cannot parse source code. Source code contains tab character. Exiting with code 1.");
            std::cerr << "ERROR: Source code contains tab!" << std::endl;
            file.close();
            std::exit(1);
        }

        m_sourceCode = split_wstr(fileData, L"\n");
    }
    else
    {
        std::cerr << "Cannot open \"" << m_filename << "\"" << std::endl;
        defaultLogger.log(LogType::ERROR, L"Cannot open \"{}\". Exiting with code 1.", m_filename);
        std::exit(1);
    }
    defaultLogger.log(LogType::INFO, L"Finished reading source code!");
    file.close();
}

// Creates generators
void Electra::createGenerators()
{
    defaultLogger.log(LogType::INFO, L"Started parsing generators from source code!");
    for(std::size_t y = 0; y < m_sourceCode.size(); y++)
    {
        for(std::size_t x = 0; x < m_sourceCode[y].size(); x++)
        {
            char_t currentChar = m_sourceCode.at(y).at(x);
            
            for(auto &c : m_generatorChars)
            {
                if(c == currentChar)
                {
                    GeneratorData* genData = &m_generatorDataMap[c];
                    defaultLogger.log(LogType::INFO, L"Found a generator at ({}, {}).", x, y);
                    m_generators.push_back( std::make_shared<Generator>(
                        *genData,
                        Position(x, y)
                    ) );
                }
            }
        }
    }
    defaultLogger.log(LogType::INFO, L"Finished parsing generators from source code!");
}

/*
Creates portals.
*/
void Electra::createPortals()
{
    defaultLogger.log(LogType::INFO, L"Started parsing portals from source code!");

    for(std::size_t y = 0; y < m_sourceCode.size(); y++)
    {
        for(std::size_t x = 0; x < m_sourceCode[y].size(); x++)
        {
            char_t currentChar = m_sourceCode.at(y).at(x);
            if(currentChar == L' ' || currentChar == L'\n') continue;
            
            // If current char is a generator check next character
            if(std::find(m_generatorChars.begin(), m_generatorChars.end(), currentChar) != m_generatorChars.end()) continue;

            try
            {
                m_components.at(currentChar);
            }
            catch(const std::exception& e)
            {
                if(m_portalMap.find(currentChar) == m_portalMap.end())
                {
                    m_portalMap[currentChar] = {(int)x, (int)y};
                    defaultLogger.log(LogType::INFO, L"Found a portal at ({}, {}).", x, y);
                }
            }
            
        }
    }

    for(auto &p : m_portalMap)
    {
        m_components[p.first] = std::make_unique<Portal>(p.second);
    }
    defaultLogger.log(LogType::INFO, L"Finished parsing portals from source code!");
}

/*
Updates generators.
Generators will generate new current if they can.
*/
void Electra::generateGenerators()
{
    for(auto &gen : m_generators)
        gen->generate(&m_currents, &m_stacks[0]);
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
            defaultLogger.log(LogType::INFO, L"Removing current at ({},{}) with direction {} (Y coordinate out of bounds)", curPos.x, curPos.y, cur->getDirection());
            continue;
        }
        if(curPos.x < 0 || curPos.x >= m_sourceCode[curPos.y].size())
        {
            m_deadCurrentIndexes.push_back(i);
            defaultLogger.log(LogType::INFO, L"Removing current at ({},{}) with direction {} (X coordinate out of bounds)", curPos.x, curPos.y, cur->getDirection());
            continue;
        }

        // Main part that determines functionality of the current
        char_t currentChar = m_sourceCode[curPos.y][curPos.x];
        try
        {
            // throws an error if currentChar is not a key of m_components
            auto &comp = m_components.at(currentChar);
            if(!comp->work(cur, &m_newCurrents))
            {
                m_deadCurrentIndexes.push_back(i);
                defaultLogger.log(LogType::INFO, L"Removing current at ({},{}) with direction {} (Component refused to work.)", curPos.x, curPos.y, cur->getDirection());
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
                    defaultLogger.log(LogType::INFO, L"Removing current at ({},{}) with direction {} (Current does not align with generator)", curPos.x, curPos.y, cur->getDirection());
                }
            }
            else
            {
                m_deadCurrentIndexes.push_back(i);
                defaultLogger.log(LogType::INFO, L"Removing current at ({},{}) with direction {} (Not a component nor generator.)", curPos.x, curPos.y, cur->getDirection());
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
    defaultLogger.log(LogType::INFO, L"Started creating currents!");
    for(auto &cur : m_newCurrents)
    {
        Position curPos = cur->getPosition();
        m_currents.push_back(cur);
    }
    
    m_newCurrents.clear();

    defaultLogger.log(LogType::INFO, L"Total current count: {}.", m_currents.size());
    defaultLogger.log(LogType::INFO, L"Finished creating currents!");
}

void Electra::sigHandler(int signal)
{
    Electra::m_isRunning = false;
}
