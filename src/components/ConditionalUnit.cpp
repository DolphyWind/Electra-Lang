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

#include <components/ConditionalUnit.hpp>
#include <utility/Logger.hpp>

ConditionalUnit::ConditionalUnit(const std::vector<Direction>& directions, var_t targetValue, bool isInverted,
                                 bool checkEqual, bool checkLess, bool checkGreater):
    Cable(directions), m_targetValue(targetValue), m_inverted(isInverted), m_checkEqual(checkEqual), m_checkLess(checkLess), m_checkGreater(checkGreater)
{}

bool ConditionalUnit::work(Current::Ptr current, std::vector<Current::Ptr>& currentVector)
{
    if(!Component::work(current, currentVector))
    {
        return false;
    }
    if(current->stackPtr->empty())
    {
        return Cable::work(current, currentVector);
    }

    var_t top = Global::popStack(current->stackPtr);

    bool result = true;
    result = (!m_checkEqual || (top == m_targetValue));
    result = result && (!m_checkLess || (top < m_targetValue));
    result = result && (!m_checkGreater || (top > m_targetValue));
    result = (m_inverted == !result);

    defaultLogger.log(LogType::INFO, "(ConditionalUnit) Comparing {} with {}. Result: {}. (invert: {}, checkequal: {}, checkless: {}, checkgreater: {})", top, m_targetValue, result, m_inverted, m_checkEqual, m_checkLess, m_checkGreater);
    return result && Cable::work(current, currentVector);
}