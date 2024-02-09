#include <FileCloser.hpp>
#include <FileDescriptorManager.hpp>
#include <Logger.hpp>

FileCloser::FileCloser(const std::vector<Direction>& directions):
    Cable(directions)
{}

bool FileCloser::work(Current::Ptr current, std::vector<Current::Ptr>& currentVector)
{
    if(!Component::work(current, currentVector))
    {
        return false;
    }

    if(current->stackPtr->empty())
    {
        defaultLogger.log(LogType::WARNING, "(FileCloser) Stack is empty! There are no file id to close.");
        return Cable::work(current, currentVector);
    }

    std::size_t id = Global::popStack(current->stackPtr, 0);
    if(!FileDescriptorManager::close(id))
    {
        defaultLogger.log(LogType::WARNING, "(FileCloser) Unable to close file with id {}. Pushing 0 to stack.", id);
        current->stackPtr->push(0);
    }
    else
    {
        defaultLogger.log(LogType::INFO, "(FileCloser) Closed file with id {}.", id);
    }

    return Cable::work(current, currentVector);
}