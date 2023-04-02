#pragma once
#include <stack>
#include <Logger.hpp>
#include <string>
#include <sstream>
#include <fstream>

typedef double var_t;
typedef std::stack<var_t>* StackPtr;
typedef unsigned char char_t;
typedef std::string string_t;
typedef std::stringstream stringstream_t;
typedef std::ifstream ifstream_t;

// Pops the top value of stack. Returns defaultValue if there is no item.
var_t popStack(StackPtr stack, var_t defaultValue = 0);