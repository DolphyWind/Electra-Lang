#include "Printer.hpp"

bool Printer::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    std::uint32_t top = 0;

    if(!m_stackPtr->empty())
    {
        top = m_stackPtr->top();
        m_stackPtr->pop();
    }

    if(m_printAsAscii)
        std::cout << (unsigned char) top;
    else
        std::cout << top;

    return true;
}