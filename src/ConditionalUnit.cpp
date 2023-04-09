/**
MIT License

Copyright (c) 2023 Yunus Emre Aydın

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <ConditionalUnit.hpp>

bool ConditionalUnit::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(current->stackPtr->empty())
        return true;
    
    var_t x = popStack(current->stackPtr);
    bool condition = (x != m_targetValue);

    if(condition) defaultLogger.log(LogType::INFO, L"(ConditionalUnit) {} is not equals to {}.", x, m_targetValue);
    else defaultLogger.log(LogType::INFO, L"(ConditionalUnit) {} is equals to {}.", x, m_targetValue);
    if(m_invert) condition = !condition;
    
    if(condition) defaultLogger.log(LogType::INFO, L"(ConditionalUnit) Current will pass.");
    else defaultLogger.log(LogType::INFO, L"(ConditionalUnit) Current will not pass.");

    return condition;
}