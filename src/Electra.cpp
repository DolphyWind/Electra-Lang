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

#include <cmath>
#include <sstream>

#include <boost/regex.hpp>
#include <thirdparty/dylib/dylib.hpp>

#include <Electra.hpp>
#include <utility/ArgParser.hpp>
#include <components/ArithmeticalUnit.hpp>
#include <components/Bomb.hpp>
#include <components/Cloner.hpp>
#include <components/CloningDynamicComponent.hpp>
#include <components/ConditionalUnit.hpp>
#include <components/ConstantAdder.hpp>
#include <components/ConstantPusher.hpp>
#include <components/Eraser.hpp>
#include <components/Key.hpp>
#include <utility/Logger.hpp>
#include <components/NonCloningDynamicComponent.hpp>
#include <components/Portal.hpp>
#include <components/Printer.hpp>
#include <components/Reader.hpp>
#include <components/Reverser.hpp>
#include <components/StackChecker.hpp>
#include <components/StackSwitcher.hpp>
#include <components/Swapper.hpp>
#include <components/FileReader.hpp>
#include <components/FileOpener.hpp>
#include <components/FileWriter.hpp>
#include <components/FileCloser.hpp>
using namespace std::string_literals;

Electra::Electra():
    m_currentPath(fs::current_path())
{
    setupComponentsAndGenerators();
    setupSignalHandlers();
}

Electra::Electra(const std::vector<std::string>& args):
    Electra()
{
    // Creates argument parser and parses command line arguments.
    ArgParser parser(args);
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

    defaultLogger.loggingEnabled = bool_map["log"];
    if(bool_map["help"])
    {
        parser.printHelpMessage();
        defaultLogger.log(LogType::INFO, "Printed help message. Exiting with code 0.");
        Global::safe_exit(0);
    }

    if(bool_map["version"])
    {
        parser.printVersionMessage();
        defaultLogger.log(LogType::INFO, "Printed current version of electra. Exiting with code 0.");
        Global::safe_exit(0);
    }
    
    if(alone_args.empty())
    {
        parser.printHelpMessage();
        defaultLogger.log(LogType::INFO, "No arguments specified. Printing help message. Exiting with code 1.");
        Global::safe_exit(1);
    }

    std::string stack_count_str = string_map["stack-count"];

    // Parses --stack-count argument
    // Example: --stack-count 32
    // Makes the size of m_stacks
    try
    {
        long stack_count;
        if(stack_count_str.empty())
        {
            stack_count = Electra::default_stack_count;
        }
        else
        {
            stack_count = std::stol(stack_count_str);
        }
        if(stack_count <= 0)
        {
            throw std::invalid_argument("Stack count should be greater than zero!");
        }
        
        m_stacks.resize(stack_count);
    }
    catch (const std::invalid_argument &e)
    {
        defaultLogger.log(LogType::ERROR, "\"{}\" is invalid for stack-count.\n");
        std::cerr << '\"' << stack_count_str << "\" is invalid for stack-count.\n";
        Global::safe_exit(1);
    }
    catch (const std::out_of_range &e)
    {
        defaultLogger.log(LogType::ERROR, "\"{}\" is out of range for stack-count.", stack_count_str);
        std::cerr << '\"' << stack_count_str << "\" is out of range for stack-count." << std::endl;
        Global::safe_exit(1);
    }

    // Parses --stack argument
    // Example: --stack "1 2 3,4 5 6"
    // First stack contains 123 and second stack contains 456
    std::size_t index = 0;
    auto split_by_comma = sutil::split(string_map["stack"], ",");
    if(split_by_comma.size() > m_stacks.size())
    {
        std::cerr << "You entered initial values for " << split_by_comma.size() << " stacks but stack count is " << m_stacks.size() << "!" << std::endl;
        defaultLogger.log(LogType::ERROR, "You entered initial values for {} stacks but stack count is {}!", split_by_comma.size(), m_stacks.size());
        Global::safe_exit(1);
    }
    for(auto &split : split_by_comma)
    {
        for(auto &i : sutil::split(split, " "))
        {
            if(i.empty()) continue;

            try
            {
                m_stacks[index].push(std::stod(i));
            }
            catch(const std::out_of_range &e)
            {
                defaultLogger.log(LogType::ERROR, "The value {} is too big or small for var_t.", i);
                std::cerr << "The value " << i << " is too big or small for var_t." << std::endl;
                Global::safe_exit(1);
            }
            catch(const std::invalid_argument &e)
            {
                defaultLogger.log(LogType::ERROR, "Can\'t convert {} to var_t.", i);
                std::cerr << "Can\'t convert " << i << " to var_t." << std::endl;
                Global::safe_exit(1);
            }
        }
        index ++;
    }

    m_filename = alone_args[0];
    loadSourceFromFile(m_filename);
}

void Electra::setSourceCode(const std::string& sourceCode)
{
    cleanup();
    setupComponentsAndGenerators();

    auto content = parseSourceCode(m_currentPath, sourceCode);
    for(auto& line : content)
    {
        std::u32string line32;
        utf8::utf8to32(line.begin(), line.end(), std::back_inserter(line32));
        m_sourceCode.emplace_back(std::move(line32));
    }
    createGenerators();
    createPortals();
    m_currentPath = fs::current_path();
}

void Electra::loadSourceFromFile(const std::string& filepath)
{
    fs::path total_path = m_currentPath / filepath;
    m_currentPath = total_path.parent_path();

    if(!fs::exists(total_path) || !fs::is_regular_file(total_path))
    {
        std::cerr << "Invalid file: " << total_path.string() << std::endl;
        defaultLogger.log(LogType::ERROR, "Invalid file: {}", total_path.string());
        Global::safe_exit(1);
    }

    std::ifstream ifs(total_path.string());
    if(!ifs.good())
    {
        std::cerr << "Cannot open \"" << filepath << '\"' << std::endl;
        defaultLogger.log(LogType::ERROR, "Cannot open \"{}\". Exiting with code 1.", filepath);
        Global::safe_exit(1);
    }

    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    setSourceCode(ss.str());
}

void Electra::cleanup()
{
    m_components.clear();
    m_generatorDataMap.clear();
    m_generatorChars.clear();
    m_generators.clear();
    m_currents.clear();
    m_filename.clear();
    m_sourceCode.clear();
    m_includedParts.clear();
    m_deadCurrentIndices.clear();
    m_newCurrents.clear();
    m_portalMap.clear();
    m_dynamicLibraries.clear();
}

std::vector<std::string> Electra::includeFile(const fs::path& currentPath, const std::string& filename, LineRange lineRange)
{
    if(lineRange.getBegin() == lineRange.getEnd())
    {
        return {};
    }

    fs::path total_path = currentPath / filename;
    fs::path parent_path = total_path.parent_path();
    std::string total_path_str = total_path.string();

    if(!fs::exists(total_path) || !fs::is_regular_file(total_path))
    {
        std::cerr << "Invalid file: " << total_path.string() << std::endl;
        defaultLogger.log(LogType::ERROR, "Invalid file: {}", total_path.string());
        Global::safe_exit(1);
    }

    std::ifstream ifs(total_path_str);
    if(!ifs.good())
    {
        std::cerr << "Cannot open \"" << filename << '\"' << std::endl;
        defaultLogger.log(LogType::ERROR, "Cannot open \"{}\". Exiting with code 1.", filename);
        Global::safe_exit(1);
    }

    std::stringstream ss;
    ss << ifs.rdbuf();
    std::string content_str = ss.str();
    ifs.close();

    auto content = parseSourceCode(currentPath, content_str, lineRange);
    m_includedParts[total_path.string()].insert(lineRange);
    return content;
}

std::vector<std::string> Electra::parseSourceCode(const fs::path& currentPath, const std::string& sourceCode, LineRange lineRange)
{
    std::vector<std::string> content = sutil::split(sourceCode, "\n");
    if(lineRange.getEnd() > content.size() + 1)
    {
        lineRange.setEnd(content.size() + 1);
    }

    typedef std::vector<std::string>::difference_type diff_type;
    content = std::vector<std::string>(content.begin() + static_cast<diff_type>(lineRange.getBegin() - 1), content.begin() + static_cast<diff_type>(lineRange.getEnd() - 1));
    for(std::size_t i = 0; i < content.size();)
    {
        beginLoop:

        auto& line = content[i];
        if(line.find('\t') != std::string::npos)
        {
            defaultLogger.log(LogType::ERROR, "Source code contains tab character. Exiting with code 1.");
            std::cerr << "Error while reading file: Source code contains tab!" << std::endl;
            Global::safe_exit(1);
        }

        sutil::remove_comments(line);
        std::optional<std::string> includePatternMatch = sutil::get_matched_string(line, boost::regex("\"([^\"]+)\"(?:\\s*([^:]+:[^\"]*))?"));
        if(!includePatternMatch.has_value())
        {
            ++i;
            continue;
        }
        content.erase(content.begin() + static_cast<diff_type>(i));
        std::string includePatternStr = includePatternMatch.value();

        std::size_t first_quotation_mark_pos = includePatternStr.find('\"');
        std::size_t second_quotation_mark_pos = includePatternStr.find('\"', first_quotation_mark_pos + 1);
        std::string new_filename = includePatternStr.substr(first_quotation_mark_pos, second_quotation_mark_pos - first_quotation_mark_pos + 1);
        new_filename = std::string(std::next(new_filename.begin()), std::prev(new_filename.end()));

        if(new_filename.ends_with(WIN_MAC_OTHER(".dll", ".dylib", ".so")))
        {
            // It is a dynamic component
            loadDynamicComponent(m_currentPath, new_filename);
            continue;
        }
        std::string line_range_str = includePatternStr.substr(new_filename.size() + 2);

        fs::path new_file_path = currentPath / new_filename;
        fs::path parent_path = new_file_path.parent_path();
        std::string raw_filename = fs::path(new_filename).filename().string();
        std::string new_file_path_str = new_file_path.string();

        bool allow_reinclusion = new_filename.starts_with('!');
        if(allow_reinclusion)
        {
            new_filename.erase(new_filename.begin());
        }

        line_range_str = sutil::remove_spaces(line_range_str);
        LineRange new_line_range;
        std::vector<std::string> split_from_colon = sutil::split(line_range_str, ":");

        if(!fs::exists(new_file_path) || !fs::is_regular_file(new_file_path))
        {
            std::cerr << "Invalid file: " << new_file_path.string() << std::endl;
            defaultLogger.log(LogType::ERROR, "Invalid file: {}", new_file_path.string());
            Global::safe_exit(1);
        }

        try
        {
            if(!split_from_colon.at(0).empty())
            {
                new_line_range.setBegin(std::stoul(split_from_colon.at(0)));
            }
            if(split_from_colon.size() > 1 && !split_from_colon.at(1).empty())
            {
                new_line_range.setEnd(std::stoul(split_from_colon.at(1)));
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Cannot convert \"" << split_from_colon.at(0) << "\" to a number." << std::endl;
            defaultLogger.log(LogType::ERROR, "Cannot convert \"{}\" to a number.", split_from_colon.at(0));
            Global::safe_exit(1);
        }

        if(!allow_reinclusion && m_includedParts.contains(new_file_path_str))
        {
            for(auto& item : m_includedParts[new_file_path_str])
            {
                if(item.intersects(new_line_range))
                {
                    defaultLogger.log(LogType::WARNING, "Prevented re-including {}.", new_filename);
                    goto beginLoop;
                }
            }
        }

        std::vector<std::string> new_content = includeFile(parent_path, raw_filename, new_line_range);
        m_includedParts[new_file_path_str].insert(new_line_range);
        content.insert(content.begin() + static_cast<diff_type>(i), new_content.begin(), new_content.end());
    }

    return content;
}

void Electra::setupComponentsAndGenerators()
{
    // Sets up cables
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

    // I ran out of visually descriptive ascii characters :(
    m_components[U'{'] = std::make_unique<Cable>( bin2dir(0b00000001), true );
    m_components[U'}'] = std::make_unique<Cable>( bin2dir(0b00010000), true );
    m_components[U'U'] = std::make_unique<Cable>( bin2dir(0b00000100), true );
    m_components[U'n'] = std::make_unique<Cable>( bin2dir(0b01000000), true );

    // Sets up Printers
    m_components[U'N'] = std::make_unique<Printer>( bin2dir(0b10111011), false);
    m_components[U'P'] = std::make_unique<Printer>( bin2dir(0b00111111), true);

    // Sets up Arithmetical Units
    m_components[U'A'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b10100100), [](var_t x, var_t y){return x + y;} );
    m_components[U'S'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b01100110), [](var_t x, var_t y){return x - y;} );
    m_components[U'M'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b11111011), [](var_t x, var_t y){return x * y;} );
    m_components[U'Q'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b11010101), [](var_t x, var_t y){return x / y;} );
    m_components[U'%'] = std::make_unique<ArithmeticalUnit>( bin2dir(0b00100010), [](var_t x, var_t y){return std::fmod(x, y);} );

    // Sets up constant adders
    m_components[U'I'] = std::make_unique<ConstantAdder>( bin2dir(0b01000100), 1);
    m_components[U'D'] = std::make_unique<ConstantAdder>( bin2dir(0b01111101), -1);

    // Sets up cloner
    m_components[U'#'] = std::make_unique<Cloner>( bin2dir(0b01010101) );

    // Sets up constant pusher
    m_components[U'O'] = std::make_unique<ConstantPusher>( bin2dir(0b11111111), 0);

    // Sets up readers
    m_components[U'@'] = std::make_unique<Reader>( bin2dir(0b01111111), false);
    m_components[U'&'] = std::make_unique<Reader>( bin2dir(0b11100101), true);

    // Sets up swapper
    m_components[U'$'] = std::make_unique<Swapper>( bin2dir(0b01100110) );

    // Sets up conditional units
    m_components[U'['] = std::make_unique<ConditionalUnit>( bin2dir(0b01000100), 0, true, true, false, false);
    m_components[U']'] = std::make_unique<ConditionalUnit>( bin2dir(0b01000100), 0, false, true, false, false);
    m_components[U'L'] = std::make_unique<ConditionalUnit>( bin2dir(0b11111000), 0, false, false, true, false);
    m_components[U'l'] = std::make_unique<ConditionalUnit>( bin2dir(0b01000100), 0, true, false, true, false);
    m_components[U'G'] = std::make_unique<ConditionalUnit>( bin2dir(0b11111101), 0, false, false, false, true);
    m_components[U'g'] = std::make_unique<ConditionalUnit>( bin2dir(0b11101110), 0, true, false, false, true);

    // Sets up stack checkers
    m_components[U'('] = std::make_unique<StackChecker>( bin2dir(0b01000100), true);
    m_components[U')'] = std::make_unique<StackChecker>( bin2dir(0b01000100), false);

    // Sets up stack switchers
    m_components[U'F'] = std::make_unique<StackSwitcher>( bin2dir(0b00111111), true, &m_stacks, false);
    m_components[U'f'] = std::make_unique<StackSwitcher>( bin2dir(0b01010111), true, &m_stacks, true);
    m_components[U'B'] = std::make_unique<StackSwitcher>( bin2dir(0b11111110), false, &m_stacks, false);
    m_components[U'b'] = std::make_unique<StackSwitcher>( bin2dir(0b11111001), false, &m_stacks, true);

    // Sets up keys
    m_components[U'~'] = std::make_unique<Key>( bin2dir(0b00010001), bin2dir(0b01000100), m_sourceCode, U'-');
    m_components[U'!'] = std::make_unique<Key>( bin2dir(0b01000100), bin2dir(0b00010001), m_sourceCode, U'|');

    // Sets up Reverser
    m_components[U'R'] = std::make_unique<Reverser>( bin2dir(0b10111111) );

    // Sets up Eraser
    m_components[U'E'] = std::make_unique<Eraser>( bin2dir(0b11111111) );

    // Sets up Bomb
    m_components[U'o'] = std::make_unique<Bomb>( bin2dir(0b11111111) );

    // Sets up File Reader
    m_components[U'r'] = std::make_unique<FileReader>( bin2dir(0b00111110) );

    // Sets up File Opener
    m_components[U'w'] = std::make_unique<FileOpener>( bin2dir(0b10110001), false );
    m_components[U'a'] = std::make_unique<FileOpener>( bin2dir(0b11101111), true );

    // Sets up File Writer
    m_components[U'W'] = std::make_unique<FileWriter>( bin2dir(0b10101110) );

    // Sets up File Closer
    m_components[U'C'] = std::make_unique<FileCloser>( bin2dir(0b11111110) );

    // Saves generator characters, their directions and toggler directions in a map
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
}

void Electra::setupSignalHandlers()
{
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

void Electra::mainLoop()
{
    defaultLogger.log(LogType::INFO, "Program started!");
    int tickCount = 0;
    generateFromGenerators();

    do
    {
        defaultLogger.log(LogType::INFO, "Tick: {}", tickCount);

        interpretCurrents();
        moveCurrents();
        removeCurrents();    
        createCurrents();

        tickCount ++;
    }while (!m_currents.empty());

    defaultLogger.log(LogType::INFO, "Program finished. Total ticks: {}", tickCount);
}

void Electra::loadDynamicComponent(const fs::path& path, const std::string& filename)
{
    if(loadDynamicComponent(filename))
    {
        return;
    }

    try
    {
        dylib lib(path.string(), filename, dylib::no_filename_decorations);
        ComponentInformation componentInformation;
        lib.get_function<void(ComponentInformation&)>("load")(componentInformation);
        auto workFuncWithStacksParam = lib.get_function<bool(std::vector<std::stack<var_t>>&, Current::Ptr, std::vector<Current::Ptr>&)>("work");
        auto workFunc = std::bind(workFuncWithStacksParam, std::ref(m_stacks), std::placeholders::_1, std::placeholders::_2);
        m_dynamicLibraries.push_back(std::move(lib));

        if(componentInformation.componentType == ComponentInformation::ComponentType::NON_CLONING)
        {
            m_components[componentInformation.symbol] = std::make_unique<NonCloningDynamicComponent>(componentInformation.directions, workFunc);
            return;
        }
        m_components[componentInformation.symbol] = std::make_unique<CloningDynamicComponent>(componentInformation.directions, workFunc);
    }
    catch(const std::exception& exception)
    {
        defaultLogger.log(LogType::ERROR, "Unable to load \"{}\". Error message: {}", filename, exception.what());
        std::cerr << "Unable to load \"" << filename << "\" Error message: " << exception.what() << std::endl;
        Global::safe_exit(1);
    }
}

bool Electra::loadDynamicComponent(const std::string& filename)
{
    try
    {
        dylib lib(filename, dylib::no_filename_decorations);
        ComponentInformation componentInformation;
        lib.get_function<void(ComponentInformation&)>("load")(componentInformation);
        auto workFuncWithStacksParam = lib.get_function<bool(std::vector<std::stack<var_t>>&, Current::Ptr, std::vector<Current::Ptr>&)>("work");
        auto workFunc = std::bind(workFuncWithStacksParam, std::ref(m_stacks), std::placeholders::_1, std::placeholders::_2);
        m_dynamicLibraries.push_back(std::move(lib));

        if(componentInformation.componentType == ComponentInformation::ComponentType::NON_CLONING)
        {
            m_components[componentInformation.symbol] = std::make_unique<NonCloningDynamicComponent>(componentInformation.directions, workFunc);
            return true;
        }
        m_components[componentInformation.symbol] = std::make_unique<CloningDynamicComponent>(componentInformation.directions, workFunc);
        return true;
    }
    catch(const std::exception& exception)
    {
        return false;
    }
}

void Electra::createGenerators()
{
    defaultLogger.log(LogType::INFO, "Started parsing generators from source code!");
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
                    defaultLogger.log(LogType::INFO, "Found a generator at ({}, {}).", x, y);

                    m_generators.push_back( std::make_shared<Generator>(
                        genData,
                        Position(static_cast<int>(x), static_cast<int>(y))
                    ) );
                }
            }
        }
    }
    defaultLogger.log(LogType::INFO, "Finished parsing generators from source code!");
}

void Electra::createPortals()
{
    defaultLogger.log(LogType::INFO, "Started parsing portals from source code!");

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
                defaultLogger.log(LogType::INFO, "Found a portal at ({}, {}).", x, y);
            }
        }
    }

    // Create portals here
    for(auto &p : m_portalMap)
    {
        m_components[p.first] = std::make_unique<Portal>(p.second);
    }
    defaultLogger.log(LogType::INFO, "Finished parsing portals from source code!");
}

void Electra::generateFromGenerators()
{
    for(auto &gen : m_generators)
    {
        gen->generate(m_currents, m_stacks.begin());
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
            m_deadCurrentIndices.push_back(i);
            defaultLogger.log(LogType::INFO, "Removing current at ({}, {}) with direction {} (Y coordinate out of bounds)", curPos.x, curPos.y, cur->getDirection());
            continue;
        }
        if(curPos.x < 0 || curPos.x >= m_sourceCode[curPos.y].size())
        {
            m_deadCurrentIndices.push_back(i);
            defaultLogger.log(LogType::INFO, "Removing current at ({}, {}) with direction {} (X coordinate out of bounds)", curPos.x, curPos.y, cur->getDirection());
            continue;
        }

        // Determines functionality of the current
        char32_t currentChar = m_sourceCode[curPos.y][curPos.x];
        if(m_components.contains(currentChar)) // It is a component
        {
            auto& comp = m_components[currentChar];
            if(!comp->work(cur, m_newCurrents))
            {
                m_deadCurrentIndices.push_back(i);
                defaultLogger.log(LogType::INFO, "Removing current at ({}, {}) with direction {} (Component refused to work.)", curPos.x, curPos.y, cur->getDirection());
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
                m_deadCurrentIndices.push_back(i);
                defaultLogger.log(LogType::INFO, "Removing current at ({}, {}) with direction {} (Current isn\'t aligned with generator)", curPos.x, curPos.y, cur->getDirection());
            }
        }
        else
        {
            m_deadCurrentIndices.push_back(i);
            defaultLogger.log(LogType::INFO, "Removing current at ({}, {}) with direction {} (Not a component nor generator.)", curPos.x, curPos.y, cur->getDirection());
        }
    }
}

void Electra::removeCurrents()
{
    std::sort(m_deadCurrentIndices.begin(), m_deadCurrentIndices.end(), std::greater<>());
    for(auto &i : m_deadCurrentIndices)
    {
        m_currents.erase(m_currents.begin() + static_cast<std::vector<Current::Ptr>::difference_type>(i));
    }
    m_deadCurrentIndices.clear();
}

void Electra::createCurrents()
{
    defaultLogger.log(LogType::INFO, "Started creating currents!");
    for(auto &cur : m_newCurrents)
    {
        m_currents.push_back(cur);
    }
    
    m_newCurrents.clear();

    defaultLogger.log(LogType::INFO, "Total current count: {}.", m_currents.size());
    defaultLogger.log(LogType::INFO, "Finished creating currents!");
}

void Electra::sigHandler([[maybe_unused]] int signal)
{
    Global::safe_exit(1);
}
