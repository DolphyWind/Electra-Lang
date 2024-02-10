#include <FileOpener.hpp>
#include <FileDescriptorManager.hpp>
#include <Logger.hpp>

FileOpener::FileOpener(const std::vector<Direction>& directions, bool appendMode):
    Cable(directions), m_appendMode(appendMode)
{}

bool FileOpener::work(Current::Ptr current, std::vector<Current::Ptr>& currentVector)
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

    defaultLogger.log(LogType::INFO, "(FileOpener) Attempting to open \"{}\". appendMode: {}.", filename, m_appendMode);
    std::optional<std::size_t> fileId;
    if(m_appendMode)
    {
        fileId = FileDescriptorManager::openFile(filename, std::ios::binary | std::ios::app);
    }
    else
    {
        fileId = FileDescriptorManager::openFile(filename, std::ios::binary | std::ios::out);
    }

    if(!fileId.has_value())
    {
        defaultLogger.log(LogType::WARNING, "(FileOpener) Unable to open \"{}\". Pushing zero to stack.", filename);
    }
    else
    {
        defaultLogger.log(LogType::INFO, "(FileOpener) Opened \"{}\". fileID: {}, appendMode: {}.", filename, fileId.value(), m_appendMode);
    }
    current->stackPtr->push( static_cast<var_t>(fileId.value_or(0)) );

    return Cable::work(current, currentVector);
}