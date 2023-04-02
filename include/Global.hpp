#pragma once
#include <stack>
#include <Logger.hpp>

typedef double var_t;
typedef std::stack<var_t>* StackPtr;
typedef unsigned char char_t;

// Pops the top value of stack. Returns defaultValue if there is no item.
var_t popStack(StackPtr stack, var_t defaultValue = 0);