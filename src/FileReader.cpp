#include <fstream>
#include <sstream>

#include <FileReader.hpp>
#include <Logger.hpp>

FileReader::FileReader(const std::vector<Direction>& directions):
    Cable(directions)
{}

bool FileReader::work(Current::Ptr current, std::vector<Current::Ptr>& currentVector)
{
    if(!Component::work(current, currentVector))
    {
        return false;
    }

    std::string filename;
    while(!current->stackPtr->empty())
    {
        char current_char = static_cast<char>(current->stackPtr->top());
        current->stackPtr->pop();

        if(current_char == 0)
        {
            break;
        }
        filename.push_back(static_cast<char>(current_char));
    }

    std::ifstream ifs(filename, std::ios::binary);
    if(ifs.fail())
    {
        defaultLogger.log(LogType::WARNING, "(FileReader) Unable to open \"{}\". Pushing 0 to stack.", filename);
        current->stackPtr->push(0);
        return Cable::work(current, currentVector);
    }

    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    std::string fileContent_utf8 = ss.str();
    std::u32string fileContent;
    fileContent.reserve(fileContent_utf8.size());
    utf8::utf8to32(fileContent_utf8.begin(), fileContent_utf8.end(), std::back_inserter(fileContent));

    while(!fileContent.empty())
    {
        current->stackPtr->push(static_cast<var_t>( fileContent[fileContent.length() - 1] ));
        fileContent.pop_back();
    }
    defaultLogger.log(LogType::INFO, "(FileReader) Read \"{}\".", filename);

    return Cable::work(current, currentVector);
}
