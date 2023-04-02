#include <Global.hpp>

var_t popStack(StackPtr stack, var_t defaultValue)
{
    if(stack->empty())
    {
        defaultLogger.log(LogType::WARNING, "The stack you tried to pop is empty. Returning {}.", defaultValue);
        return defaultValue;
    }

    var_t top = stack->top();
    stack->pop();
    return top;
}