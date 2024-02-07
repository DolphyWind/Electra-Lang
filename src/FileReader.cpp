#include <FileReader.hpp>
#include <fstream>
#include <sstream>

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

    return Cable::work(current, currentVector);
}
