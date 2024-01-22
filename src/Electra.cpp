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

#include <Electra.hpp>
#include <fstream>
#include <sstream>
#include <algorithm>
#define _VARIADIC_MAX INT_MAX
using namespace std::string_literals;

Electra::Electra(int argc, char** argv)
{
    // Get the current folder
    m_currentPath = fs::current_path();

    // Creates argument parser and parses command line arguments.
    Argparser parser(argc, argv);
    parser.program_name = "Electra";
    parser.binary_name = "electra";
    parser.program_description = "Electra is an esolang where you code like an electrician.\n" \
    "Find more about electra at https://github.com/DolphyWind/Electra-Lang";

    parser.addArgument("--help", "-h", true, "Print this message and exit.");
    parser.addArgument("--version", "-v", true, "Print version and exit.");
    parser.addArgument("--log", "-l", true, "Enables logging. Electra logs each step of the program and saves it into a file.");
    parser.addArgument("--stack", "-s", false, "Specify the initial values of stack.");
    parser.addArgument("--stack-count", "-sc", false, "Specify the total stack count that electra uses. Must be greater than or equal to one.");

    auto parser_args = parser.parse();
    auto string_map = std::get<0>(parser_args);
    auto bool_map = std::get<1>(parser_args);
    auto alone_args = parser.getAloneArguments();

    defaultlogger.loggingEnabled = bool_map["log"];
    if(bool_map["help"])
    {
        parser.printHelpMessage();
        defaultlogger.log(LogType::INFO, "Printed help message. Exiting with code 0.");
        Global::safe_exit(0);
    }

    if(bool_map["version"])
    {
        parser.printVersionMessage();
        defaultlogger.log(LogType::INFO, "Printed current version of electra. Exiting with code 0.");
        Global::safe_exit(0);
    }
    
    if(alone_args.empty())
    {
        parser.printHelpMessage();
        defaultlogger.log(LogType::INFO, "No arguments specified. Printing help message. Exiting with code 1.");
        Global::safe_exit(1);
    }

    std::string stack_count_str = string_map["stack-count"];
    long stack_count = 0;
    
    // Parses --stack-count argument
    // Example: --stack-count 32
    // Makes the size of m_stacks 
    try
    {
        if(stack_count_str.empty()) stack_count = Electra::default_stack_count;
        else stack_count = std::stol(stack_count_str);
        if(stack_count <= 0) throw std::invalid_argument("Stack count should be greater than zero!");
        
        m_stacks.reserve(stack_count);
        for(std::size_t i = 0; i < stack_count; i++)
        {
            m_stacks.emplace_back();
        }
    }
    catch (const std::invalid_argument &e)
    {
        defaultlogger.log(LogType::ERROR, "\"{}\" is invalid for stack-count.\n");
        std::cerr << '\"' << stack_count_str << "\" is invalid for stack-count.\n";
        Global::safe_exit(1);
    }
    catch (const std::out_of_range &e)
    {
        defaultlogger.log(LogType::ERROR, "\"{}\" is out of range for stack-count.", stack_count_str);
        std::cerr << '\"' << stack_count_str << "\" is out of range for stack-count." << std::endl;
        Global::safe_exit(1);
    }

    // Parses --stack argument
    // Example: --stack "1 2 3,4 5 6"
    // First stack contains 123 and second stack contains 456
    std::size_t index = 0;
    auto splitted_by_comma = Global::split(string_map["stack"], ",");
    if(splitted_by_comma.size() > m_stacks.size())
    {
        std::cerr << "You entered initial values for " << splitted_by_comma.size() << " stacks but stack count is " << m_stacks.size() << "!" << std::endl;
        defaultlogger.log(LogType::ERROR, "You entered initial values for {} stacks but stack count is {}!", splitted_by_comma.size(), m_stacks.size());
        Global::safe_exit(1);
    }
    for(auto &splitted : splitted_by_comma)
    {
        for(auto &i : Global::split(splitted, " "))
        {
            if(i.empty()) continue;

            try
            {
                m_stacks[index].push(std::stod(i));
            }
            catch(const std::out_of_range &e)
            {
                defaultlogger.log(LogType::ERROR, "The value {} is too big or small for var_t.", i);
                std::cerr << "The value " << i << " is too big or small for var_t." << std::endl;
                Global::safe_exit(1);
            }
            catch(const std::invalid_argument &e)
            {
                defaultlogger.log(LogType::ERROR, "Can\'t convert {} to var_t.", i);
                std::cerr << "Can\'t convert " << i << " to var_t." << std::endl;
                Global::safe_exit(1);
            }
        }
        index ++;
    }
    
    m_filename = alone_args[0];

    /// Initializes components and gereators.
    // Initializes cables
    m_components[U'-'] = std::make_unique<Cable>( bin2dir(0b00010001) );
    m_components[U'⎯'] = std::make_unique<Cable>( bin2dir(0b00010001) );
    
    m_components[U'|'] = std::make_unique<Cable>( bin2dir(0b01000100) );
    
    m_components[U'/'] = std::make_unique<Cable>( bin2dir(0b00100010) );
    m_components[U'╱'] = std::make_unique<Cable>( bin2dir(0b00100010) );
    
    m_components[U'\\'] = std::make_unique<Cable>( bin2dir(0b10001000) );
    m_components[U'╲'] = std::make_unique<Cable>( bin2dir(0b10001000) );
    
    m_components[U'+'] = std::make_unique<Cable>( bin2dir(0b01010101) );
    m_components[U'┼'] = std::make_unique<Cable>( bin2dir(0b01010101) );
    
    m_components[U'X'] = std::make_unique<Cable>( bin2dir(0b10101010) );
    m_components[U'╳'] = std::make_unique<Cable>( bin2dir(0b10101010) );
    
    m_components[U'*'] = std::make_unique<Cable>( bin2dir(0b11111111) );
    m_components[U'✱'] = std::make_unique<Cable>( bin2dir(0b11111111) );

    m_components[U'╰'] = std::make_unique<Cable>( bin2dir(0b00000101) );
    m_components[U'└'] = std::make_unique<Cable>( bin2dir(0b00000101) );

    m_components[U'╯'] = std::make_unique<Cable>( bin2dir(0b00010100) );
    m_components[U'┘'] = std::make_unique<Cable>( bin2dir(0b00010100) );

    m_components[U'╭'] = std::make_unique<Cable>( bin2dir(0b01000001) );
    m_components[U'┌'] = std::make_unique<Cable>( bin2dir(0b01000001) );

    m_components[U'┐'] = std::make_unique<Cable>( bin2dir(0b01010000) );
    m_components[U'╮'] = std::make_unique<Cable>( bin2dir(0b01010000) );

    m_components[U'├'] = std::make_unique<Cable>( bin2dir(0b00010101) );
    m_components[U'┤'] = std::make_unique<Cable>( bin2dir(0b01010100) );
    m_components[U'┬'] = std::make_unique<Cable>( bin2dir(0b01010001) );
    m_components[U'┴'] = std::make_unique<Cable>( bin2dir(0b00010101) );

    // I ran out of good ascii characters :(
    m_components[U'{'] = std::make_unique<Cable>( bin2dir(0b00000001), true );
    m_components[U'}'] = std::make_unique<Cable>( bin2dir(0b00010000), true );
    m_components[U'U'] = std::make_unique<Cable>( bin2dir(0b00000100), true );
    m_components[U'n'] = std::make_unique<Cable>( bin2dir(0b01000000), true );
    
    // Initializes Printers
    m_components[U'N'] = std::make_unique<Printer>( bin2dir(0b10111011), false);
    m_components[U'P'] = std::make_unique<Printer>( bin2dir(0b00111111), true);
    
    // Initializes Arithmatical Units
    m_components[U'A'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b10100100), [](var_t x, var_t y){return x + y;} );
    m_components[U'S'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b01100110), [](var_t x, var_t y){return x - y;} );
    m_components[U'M'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b11111011), [](var_t x, var_t y){return x * y;} );
    m_components[U'Q'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b11010101), [](var_t x, var_t y){return x / y;} );
    m_components[U'%'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b00100010), [](var_t x, var_t y){return std::fmod(x, y);} );

    // Initializes constant adders
    m_components[U'I'] = std::make_unique<ConstantAdder>( bin2dir(0b01000100), 1);
    m_components[U'D'] = std::make_unique<ConstantAdder>( bin2dir(0b01111101), -1);
    
    // Initializes cloner
    m_components[U'#'] = std::make_unique<Cloner>( bin2dir(0b01010101) );

    // Initializes constant pusher
    m_components[U'O'] = std::make_unique<ConstantPusher>( bin2dir(0b11111111), 0);
    
    // Initializes readers
    m_components[U'@'] = std::make_unique<Reader>( bin2dir(0b01111111), false);
    m_components[U'&'] = std::make_unique<Reader>( bin2dir(0b11100101), true);

    // Initializes swapper
    m_components[U'$'] = std::make_unique<Swapper>( bin2dir(0b01100110) );

    // Initializes conditional units
    m_components[U'['] = std::make_unique<ConditionalUnit>( bin2dir(0b01000100), 0, true, true, false, false);
    m_components[U']'] = std::make_unique<ConditionalUnit>( bin2dir(0b01000100), 0, false, true, false, false);
    m_components[U'L'] = std::make_unique<ConditionalUnit>( bin2dir(0b11111000), 0, false, false, true, false);
    m_components[U'l'] = std::make_unique<ConditionalUnit>( bin2dir(0b01000100), 0, true, false, true, false);
    m_components[U'G'] = std::make_unique<ConditionalUnit>( bin2dir(0b11111101), 0, false, false, false, true);
    m_components[U'g'] = std::make_unique<ConditionalUnit>( bin2dir(0b11101110), 0, true, false, false, true);
    
    // Initializes stack checkers
    m_components[U'('] = std::make_unique<StackChecker>( bin2dir(0b01000100), true);
    m_components[U')'] = std::make_unique<StackChecker>( bin2dir(0b01000100), false);

    // Initializes stack switchers
    m_components[U'F'] = std::make_unique<StackSwitcher>( bin2dir(0b00111111), true, &m_stacks, false);
    m_components[U'f'] = std::make_unique<StackSwitcher>( bin2dir(0b01010111), true, &m_stacks, true);
    m_components[U'B'] = std::make_unique<StackSwitcher>( bin2dir(0b11111110), false, &m_stacks, false);
    m_components[U'b'] = std::make_unique<StackSwitcher>( bin2dir(0b11111001), false, &m_stacks, true);

    // Initializes keys
    m_components[U'~'] = std::make_unique<Key>( bin2dir(0b00010001), bin2dir(0b01000100), m_sourceCode, U'-');
    m_components[U'!'] = std::make_unique<Key>( bin2dir(0b01000100), bin2dir(0b00010001), m_sourceCode, U'|');
    
    // Initializes Reverser
    m_components[U'R'] = std::make_unique<Reverser>( bin2dir(0b10111111) );
    
    // Initializes Eraser
    m_components[U'E'] = std::make_unique<Eraser>( bin2dir(0b11111111) );

    // Initializes Bomb
    m_components[U'o'] = std::make_unique<Bomb>( bin2dir(0b11111111));

    // Saves generator characters and their directions and toggler directions in a map
    m_generatorDataMap[U'>'] = bin2dir(0b00000001);
    m_generatorDataMap[U'→'] = bin2dir(0b00000001);

    m_generatorDataMap[U'^'] = bin2dir(0b00000100);
    m_generatorDataMap[U'↑'] = bin2dir(0b00000100);
    
    m_generatorDataMap[U'<'] = bin2dir(0b00010000);
    m_generatorDataMap[U'←'] = bin2dir(0b00010000);
    
    m_generatorDataMap[U'v'] = bin2dir(0b01000000);
    m_generatorDataMap[U'↓'] = bin2dir(0b01000000);
    
    m_generatorDataMap[U'↔'] = bin2dir(0b00010001);
    m_generatorDataMap[U'↕'] = bin2dir(0b01000100);
    m_generatorDataMap[U'↗'] = bin2dir(0b00000010);
    m_generatorDataMap[U'↖'] = bin2dir(0b00001000);
    m_generatorDataMap[U'↙'] = bin2dir(0b00100000);
    m_generatorDataMap[U'↘'] = bin2dir(0b10000000);
    
    // Saves generator chars separately
    for(auto &p : m_generatorDataMap)
    {
        m_generatorChars.push_back(p.first);
    }

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
    #ifdef SIGABRT
    signal(SIGABRT, &Electra::sigHandler);
    #endif
}

void Electra::run()
{
    std::vector<std::string> sourceCodeUtf8 = includeFile(m_currentPath, m_filename);
    removeComments(sourceCodeUtf8);

    m_sourceCode.reserve(sourceCodeUtf8.size());
    for(const auto& line : sourceCodeUtf8)
    {
        std::u32string str;
        utf8::utf8to32(line.begin(), line.end(), str.begin());

        m_sourceCode.push_back(str);
    }
    createGenerators();
    createPortals();
    mainLoop();
}

void Electra::mainLoop()
{
    defaultlogger.log(LogType::INFO, "Program started!");
    int tickCount = 0;
    generateGenerators();

    do
    {
        defaultlogger.log(LogType::INFO, "Tick: {}", tickCount);

        interpretCurrents();
        moveCurrents();
        removeCurrents();    
        createCurrents();

        tickCount ++;
    }while (!m_currents.empty());

    defaultlogger.log(LogType::INFO, "Program finished. Total ticks: {}", tickCount);
}

std::vector<std::string> Electra::includeFile(fs::path currentPath, const std::string& filename, std::size_t start, std::size_t end, bool allow_reinclusion)
{
    // Start cannot be greater than the end
    if(start >= end)
    {
        std::cerr << "Inclusion failed: Start line number has to be less than the end line number." << std::endl;
        defaultlogger.log(LogType::ERROR, "Inclusion failed: Start line number has to be less than the end line number.");
        Global::safe_exit(1);
    }

    // Fix here
    if(!allow_reinclusion)
    {
        std::string total_path = (currentPath / filename).string();
        if(m_includedParts.contains(total_path))
        {
            // Check if a re-inclusion has happened
            auto &range = m_includedParts[total_path];
            if( (range.first <= start && start < range.second) || (range.first <= end - 1 && end - 1 < range.second))
            {
                defaultlogger.log(LogType::WARNING, "Prevented re-including {}. Pass --allow-reinclusion as a command line argument to enable re-inclusion.", total_path);
                return {};
            }
        }
        m_includedParts[total_path] = {start, end};
    }

    // Start reading source code
    std::vector<std::string> content;
    defaultlogger.log(LogType::INFO, "Reading \"{}\".", filename);
    currentPath /= filename;

    std::ifstream file(currentPath);
    currentPath = currentPath.parent_path();

    if(file.good())
    {
        // Read file content into wss
        std::string fileData;
        std::stringstream ss;
        ss << file.rdbuf();
        fileData = ss.str();
        file.close();

        // If there is tab character exit immediately since tabsize may vary editor to editor
        if(fileData.find('\t') != std::string::npos)
        {
            defaultlogger.log(LogType::ERROR, "Cannot parse \"{}\". Source code contains tab character. Exiting with code 1.", filename);
            std::cerr << "Error while reading file: Source code contains tab!" << std::endl;
            Global::safe_exit(1);
        }

        // Split by the new line and slice file according to given parameters
        content = Global::split(fileData, "\n");
        if(end > content.size()) end = content.size();
        content = std::vector<std::string>(content.begin() + start, content.begin() + end);
        removeComments(content);

        // Include other files if there is any
        std::regex include_pattern("\".*?\"\\s*(?:[^:]?+:[^']?+)?"); // The regex pattern to match text within double quotation marks
        std::smatch match;
        for(std::size_t i = content.size() - 1; true; i--)
        {
            if(std::regex_search(content[i], match, include_pattern))
            {
                std::string match_str = match.str();

                std::regex filename_pattern("^\"([^\"]*)\"");
                std::smatch filename_match;
                std::regex_search(match_str, filename_match, filename_pattern);

                std::string new_filename = filename_match.str();
                new_filename = std::string(new_filename.begin() + 1, new_filename.end() - 1);
                std::size_t new_start = 0;
                std::size_t new_end = std::string::npos;
                
                match_str = match_str.substr(filename_match.str().size(), std::string::npos);
                match_str = Global::remove_spaces(match_str);
                
                if(match_str.find(':') != std::string::npos)
                {
                    // Determines new_start and new_end by parsing x:y
                    auto split_from_colon = Global::split(match_str, ":");

                    try
                    {
                        if(split_from_colon.at(0).empty()) new_start = 0;
                        else new_start = std::stoul(split_from_colon.at(0));
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "Cannot convert \"" << split_from_colon.at(0) << "\" to a number." << std::endl;
                        defaultlogger.log(LogType::ERROR, "Cannot convert \"{}\" to a number.", split_from_colon.at(0));
                        Global::safe_exit(1);
                    }

                    try
                    {
                        if(split_from_colon.size() == 1 || split_from_colon.at(1).empty()) new_end = std::string::npos;
                        else new_end = std::stoul(split_from_colon.at(1));
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "Cannot convert \"" << split_from_colon.at(1) << "\" to a number." << std::endl;
                        defaultlogger.log(LogType::ERROR, "Cannot convert \"{}\" to a number.", split_from_colon.at(1));
                        Global::safe_exit(1);
                    }
                }

                bool allow_reinclusion_of_new = (new_filename[0] == '!');
                if(allow_reinclusion_of_new)
                {
                    new_filename.erase(new_filename.begin());
                }

                content.erase(content.begin() + i);
                auto new_content = includeFile(currentPath, new_filename, new_start, new_end, allow_reinclusion_of_new);
                content.insert(content.begin() + i, new_content.begin(), new_content.end());
            }

            if(i == 0) break;
        }
    }
    else
    {
        std::cerr << "Cannot open \"" << filename << '\"' << std::endl;
        defaultlogger.log(LogType::ERROR, "Cannot open \"{}\". Exiting with code 1.", filename);
        Global::safe_exit(1);
    }

    return content;
}

void Electra::removeComments(std::vector<std::string>& block)
{
    // Replaces each comment with spaces
    for(auto &line : block)
    {
        bool replace_with_space = false;
        for(char& c : line)
        {
            if(c == '?')
            {
                c = ' ';
                replace_with_space = !replace_with_space;
            }
            else if(replace_with_space)
            {
                c = ' ';
            }
        }
    }
}

void Electra::createGenerators()
{
    defaultlogger.log(LogType::INFO, "Started parsing generators from source code!");
    for(std::size_t y = 0; y < m_sourceCode.size(); y++)
    {
        for(std::size_t x = 0; x < m_sourceCode[y].size(); x++)
        {
            char32_t currentChar = m_sourceCode.at(y).at(x);

            for(auto &c : m_generatorChars)
            {
                if(c == currentChar)
                {
                    GeneratorData& genData = m_generatorDataMap[c];
                    defaultlogger.log(LogType::INFO, "Found a generator at ({}, {}).", x, y);

                    m_generators.push_back( std::make_shared<Generator>(
                        genData,
                        Position(static_cast<int>(x), static_cast<int>(y))
                    ) );
                }
            }
        }
    }
    defaultlogger.log(LogType::INFO, "Finished parsing generators from source code!");
}

void Electra::createPortals()
{
    defaultlogger.log(LogType::INFO, "Started parsing portals from source code!");

    for(std::size_t y = 0; y < m_sourceCode.size(); y++)
    {
        for(std::size_t x = 0; x < m_sourceCode[y].size(); x++)
        {
            char32_t currentChar = m_sourceCode.at(y).at(x);
            if(currentChar == U' ' || currentChar == U'\n') continue;
            
            // If current char is a generator skip the process below
            if(std::find(m_generatorChars.begin(), m_generatorChars.end(), currentChar) != m_generatorChars.end()) continue;

            if(!m_components.contains(currentChar) && m_portalMap.find(currentChar) == m_portalMap.end())
            {
                m_portalMap[currentChar] = {static_cast<int>(x), static_cast<int>(y)};
                defaultlogger.log(LogType::INFO, "Found a portal at ({}, {}).", x, y);
            }
        }
    }

    // Create portals here
    for(auto &p : m_portalMap)
    {
        m_components[p.first] = std::make_unique<Portal>(p.second);
    }
    defaultlogger.log(LogType::INFO, "Finished parsing portals from source code!");
}

void Electra::generateGenerators()
{
    for(auto &gen : m_generators)
    {
        gen->generate(&m_currents, &m_stacks[0]);
    }
}

void Electra::moveCurrents()
{
    for(auto &cur : m_currents)
    {
        cur->iterate();
    }
}

void Electra::interpretCurrents()
{
    for(std::size_t i = 0; i < m_currents.size(); i++)
    {
        auto &cur = m_currents[i];
        Position curPos = cur->getPosition();

        // Out of bounds check
        if(curPos.y < 0 || curPos.y >= m_sourceCode.size())
        {
            m_deadCurrentIndexes.push_back(i);
            defaultlogger.log(LogType::INFO, "Removing current at ({}, {}) with direction {} (Y coordinate out of bounds)", curPos.x, curPos.y, cur->getDirection());
            continue;
        }
        if(curPos.x < 0 || curPos.x >= m_sourceCode[curPos.y].size())
        {
            m_deadCurrentIndexes.push_back(i);
            defaultlogger.log(LogType::INFO, "Removing current at ({}, {}) with direction {} (X coordinate out of bounds)", curPos.x, curPos.y, cur->getDirection());
            continue;
        }

        // Determines functionality of the current
        char32_t currentChar = m_sourceCode[curPos.y][curPos.x];
        if(m_components.contains(currentChar)) // It is a component
        {
            auto& comp = m_components[currentChar];
            if(!comp->work(cur, &m_newCurrents))
            {
                m_deadCurrentIndexes.push_back(i);
                defaultlogger.log(LogType::INFO, "Removing current at ({}, {}) with direction {} (Component refused to work.)", curPos.x, curPos.y, cur->getDirection());
            }
        }
        else if(std::find(m_generatorChars.begin(), m_generatorChars.end(), currentChar) != m_generatorChars.end()) // It is a generator
        {
            bool isAlignedWithGenerator = false;

            const std::vector<Direction>& directions = m_generatorDataMap[currentChar];
            for(const auto& dir : directions)
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
                defaultlogger.log(LogType::INFO, "Removing current at ({}, {}) with direction {} (Current isn\'t aligned with generator)", curPos.x, curPos.y, cur->getDirection());
            }
        }
        else
        {
            m_deadCurrentIndexes.push_back(i);
            defaultlogger.log(LogType::INFO, "Removing current at ({}, {}) with direction {} (Not a component nor generator.)", curPos.x, curPos.y, cur->getDirection());
        }
    }
}

void Electra::removeCurrents()
{
    std::sort(m_deadCurrentIndexes.begin(), m_deadCurrentIndexes.end(), std::greater<>());
    for(auto &i : m_deadCurrentIndexes)
    {
        m_currents.erase(m_currents.begin() + i);
    }
    m_deadCurrentIndexes.clear();
}

void Electra::createCurrents()
{
    defaultlogger.log(LogType::INFO, "Started creating currents!");
    for(auto &cur : m_newCurrents)
    {
        Position curPos = cur->getPosition();
        m_currents.push_back(cur);
    }
    
    m_newCurrents.clear();

    defaultlogger.log(LogType::INFO, "Total current count: {}.", m_currents.size());
    defaultlogger.log(LogType::INFO, "Finished creating currents!");
}

void Electra::sigHandler(int signal)
{
    Global::safe_exit(1);
}
