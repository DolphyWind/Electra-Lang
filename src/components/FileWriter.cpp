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
#include <components/FileWriter.hpp>
#include <utility/FileDescriptorManager.hpp>
#include <utility/Logger.hpp>

FileWriter::FileWriter(const std::vector<Direction>& directions):
    Cable(directions)
{}

bool FileWriter::work(Current::Ptr current, std::vector<Current::Ptr>& currentVector)
{
    if(!Component::work(current, currentVector))
    {
        return false;
    }

    if(current->stackPtr->empty())
    {
        defaultLogger.log(LogType::WARNING, "(FileWriter) Stack is empty. Cannot find a file id to write to.");
        return Cable::work(current, currentVector);
    }
    std::size_t fileId = Global::popStack(current->stackPtr, 0);

    std::string content;
    while(!current->stackPtr->empty())
    {
        char current_char = static_cast<char>(current->stackPtr->top());
        current->stackPtr->pop();

        if(current_char == 0)
        {
            break;
        }
        content.push_back(static_cast<char>(current_char));
    }
    defaultLogger.log(LogType::INFO, "(FileWriter) \"{}\" will be written to file with id {}.", content, fileId);

    if(!FileDescriptorManager::write(fileId, content))
    {
        defaultLogger.log(LogType::WARNING, "(FileWriter) Unable to write to file with id {}.", fileId);
        current->stackPtr->push(0);
    }

    return Cable::work(current, currentVector);
}
