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

#include <components/ArithmeticalUnit.hpp>
#include <utility/Logger.hpp>

ArithmeticalUnit::ArithmeticalUnit(const std::vector<Direction>& directions, ArithmeticalFunc func):
    Cable(directions), m_func(std::move(func))
{}

bool ArithmeticalUnit::work(Current::Ptr& current, std::vector<Current::Ptr>& currentVector)
{
    if(!Component::work(current, currentVector))
    {
        return false;
    }
    if(current->stackPtr->size() < 2)
    {
        return Cable::work(current, currentVector);
    }
    
    var_t first, second;
    first = Global::popStack(current->stackPtr);
    second = Global::popStack(current->stackPtr);
    var_t result = m_func(first, second);
    current->stackPtr->push(result);
    
    defaultLogger.log(LogType::INFO, "(ArithmeticalUnit) Passing {} and {} into an arithmetical unit. The result is: {}", first, second, result);
    return Cable::work(current, currentVector);
}
