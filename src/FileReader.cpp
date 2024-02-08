#include <FileReader.hpp>
#include <fstream>
#include <sstream>
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
        defaultLogger.log(LogType::WARNING, "Unable to open \"{}\". Pushing 0 to stack.", filename);
        current->stackPtr->push(0);
        return Cable::work(current, currentVector);
    }

    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    std::string fileContent = ss.str();

    while(!fileContent.empty())
    {
        current->stackPtr->push(static_cast<var_t>( fileContent[fileContent.length() - 1] ));
        fileContent.pop_back();
    }
    defaultLogger.log(LogType::INFO, "Read \"{}\".", filename);

    return Cable::work(current, currentVector);
}
