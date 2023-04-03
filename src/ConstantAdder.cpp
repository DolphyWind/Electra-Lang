#include "ConstantAdder.hpp"

bool ConstantAdder::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(current->stackPtr->empty()) return true;
    
    var_t var = popStack(current->stackPtr);
    var += m_constant;
    current->stackPtr->push(var);

    defaultLogger.log(LogType::INFO, L"(ConstantAdder) Added {} to the top value.", m_constant);
    return true;
}