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

#include <StackSwitcher.hpp>

StackSwitcher::StackSwitcher(const std::vector<Direction>& directions, bool moveForward, std::vector<std::stack<var_t>>* stacks, bool moveValue):
    Cable(directions), m_moveForward(moveForward), m_stacks(stacks), m_moveValue(moveValue)
{}

bool StackSwitcher::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Component::work(current, currentVector))
    {
        return false;
    }

    bool stack_empty = current->stackPtr->empty();
    var_t top = 0;
    if(!stack_empty && m_moveValue) top = Global::popStack(current->stackPtr);
    std::string message = "(StackSwitcher) Moving one stack {}.";

    if(m_moveForward)
    {
        if((++current->stackPtr) == &(*m_stacks->end())) current->stackPtr = &(*m_stacks->begin());
    }
    else
    {
        if(current->stackPtr == &(*m_stacks->begin())) current->stackPtr = &(*(m_stacks->end() - 1));
        else current->stackPtr--;
    }
    
    if(!stack_empty && m_moveValue) 
    {
        current->stackPtr->push(top);
        message += std::format(" With value {}.", top);
    }

    std::string forwardBackwardMessage = "backward";
    if(m_moveForward)
    {
        forwardBackwardMessage = "forward";
    }

    defaultlogger.log(LogType::INFO, message, forwardBackwardMessage);

    return Cable::work(current, currentVector);
}