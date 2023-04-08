#include <StackChecker.hpp>

bool StackChecker::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(current->stackPtr->empty())
    {
        if(m_returnIfEmpty)
            defaultLogger.log(LogType::INFO, L"(StackChecker) Stack is empty. Current will pass.");
        else
            defaultLogger.log(LogType::INFO, L"(StackChecker) Stack is empty. Current will not pass.");
        
        return m_returnIfEmpty;
    }

    if(!m_returnIfEmpty)
        defaultLogger.log(LogType::INFO, L"(StackChecker) Stack is empty. Current will pass.");
    else
        defaultLogger.log(LogType::INFO, L"(StackChecker) Stack is empty. Current will not pass.");
    
    return !m_returnIfEmpty;
}