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

    current->stackPtr->push(m_constant);
    defaultLogger.log(LogType::INFO, "(ConstantPusher) Pushed {} to the stack.", m_constant);
    return true;
}