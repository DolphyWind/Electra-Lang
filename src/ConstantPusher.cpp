#include "ConstantPusher.hpp"

bool ConstantPusher::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    current->stackPtr->push(m_constant);
    defaultLogger.log(LogType::INFO, L"(ConstantPusher) Pushed {} to the stack.", m_constant);
    return true;
}