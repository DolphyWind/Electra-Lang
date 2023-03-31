#include "ConstantAdder.hpp"

bool ConstantAdder::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(m_stackPtr->empty()) return true;
    
    var_t var = popStack(m_stackPtr);
    var += m_constant;
    m_stackPtr->push(var);

    defaultLogger.log(LogType::INFO, "(ConstantAdder) Added {} to the top value.", m_constant);
    return true;
}