#include "ConstantPusher.hpp"

bool ConstantPusher::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(m_getInput)
    {
        if(m_getInputAsChar)
        {
            char_t c;
            std::cin >> c;
            m_constant = c;
        }
        else
            std::cin >> m_constant;
    }

    m_stackPtr->push(m_constant);
    defaultLogger.log(LogType::INFO, "Pushed " + std::to_string(m_constant) + " to the stack.");
    return true;
}