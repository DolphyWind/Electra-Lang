#include <Printer.hpp>

bool Printer::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(current->stackPtr->empty()) return true;
    var_t top = popStack(current->stackPtr);

    if(m_printAsChar)
    {
        std::wcout << (char_t)top << std::flush;
        defaultLogger.log(LogType::INFO, L"Printed {} to screen.", std::wstring(1, (char_t)top));
    }
    else
    {
        std::wcout << top << std::flush;
        defaultLogger.log(LogType::INFO, L"Printed {} to screen.", top);
    }
    
    return true;
}