#include <FileWriter.hpp>
#include <FileDescriptorManager.hpp>
#include <Logger.hpp>

FileWriter::FileWriter(const std::vector<Direction>& directions):
    Cable(directions)
{}

bool FileWriter::work(Current::Ptr current, std::vector<Current::Ptr>& currentVector)
{
    if(!Component::work(current, currentVector))
    {
        return false;
    }

    if(current->stackPtr->empty())
    {
        defaultLogger.log(LogType::WARNING, "Stack is empty. Cannot find a file id to write to.");
        return Cable::work(current, currentVector);
    }
    std::size_t fileId = Global::popStack(current->stackPtr, 0);

    std::string content;
    while(!current->stackPtr->empty())
    {
        char current_char = static_cast<char>(current->stackPtr->top());
        current->stackPtr->pop();

        if(current_char == 0)
        {
            break;
        }
        content.push_back(static_cast<char>(current_char));
    }
    defaultLogger.log(LogType::INFO, "\"{}\" will be written to file with id {}.", content, fileId);

    if(!FileDescriptorManager::write(fileId, content))
    {
        defaultLogger.log(LogType::WARNING, "Unable to write to file with id {}.", fileId);
        current->stackPtr->push(0);
    }

    return Cable::work(current, currentVector);
}
