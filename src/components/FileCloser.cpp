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

#include <components/FileCloser.hpp>
#include <utility/FileDescriptorManager.hpp>
#include <utility/Logger.hpp>

FileCloser::FileCloser(const std::vector<Direction>& directions):
    Cable(directions)
{}

bool FileCloser::work(Current::Ptr current, std::vector<Current::Ptr>& currentVector)
{
    if(!Component::work(current, currentVector))
    {
        return false;
    }

    if(current->stackPtr->empty())
    {
        defaultLogger.log(LogType::WARNING, "(FileCloser) Stack is empty! There are no file id to close.");
        return Cable::work(current, currentVector);
    }

    std::size_t id = Global::popStack(current->stackPtr, 0);
    if(!FileDescriptorManager::close(id))
    {
        defaultLogger.log(LogType::WARNING, "(FileCloser) Unable to close file with id {}. Pushing 0 to stack.", id);
        current->stackPtr->push(0);
    }
    else
    {
        defaultLogger.log(LogType::INFO, "(FileCloser) Closed file with id {}.", id);
    }

    return Cable::work(current, currentVector);
}
