#include "Printer.hpp"

bool Printer::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    var_t top = popStack(m_stackPtr);

    if(m_printAsAscii)
    {
        std::cout << (unsigned char) top;
        defaultLogger.log(LogType::INFO, "Printed " + std::to_string((unsigned char)top) + " to screen.");
    }
    else
    {
        std::cout << top;
        defaultLogger.log(LogType::INFO, "Printed " + std::to_string(top) + " to screen.");
    }
        


    return true;
}