#include "Printer.hpp"

bool Printer::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(current->stackPtr->empty()) return true;
    var_t top = popStack(current->stackPtr);

    if(m_printAsChar)
    {
        std::cout << (char_t) top << std::flush;
        defaultLogger.log(LogType::INFO, "Printed {} to screen.", (char_t)top);
    }
    else
    {
        std::cout << top << std::flush;
        defaultLogger.log(LogType::INFO, "Printed to screen.", top);
    }
    
    return true;
}