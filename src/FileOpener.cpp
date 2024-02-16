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
#include <FileOpener.hpp>
#include <FileDescriptorManager.hpp>
#include <Logger.hpp>

FileOpener::FileOpener(const std::vector<Direction>& directions, bool appendMode):
    Cable(directions), m_appendMode(appendMode)
{}

bool FileOpener::work(Current::Ptr current, std::vector<Current::Ptr>& currentVector)
{
    if(!Component::work(current, currentVector))
    {
        return false;
    }

    std::string filename;
    while(!current->stackPtr->empty())
    {
        char current_char = static_cast<char>(current->stackPtr->top());
        current->stackPtr->pop();

        if(current_char == 0)
        {
            break;
        }
        filename.push_back(static_cast<char>(current_char));
    }

    defaultLogger.log(LogType::INFO, "(FileOpener) Attempting to open \"{}\". appendMode: {}.", filename, m_appendMode);
    std::optional<std::size_t> fileId;
    if(m_appendMode)
    {
        fileId = FileDescriptorManager::openFile(filename, std::ios::binary | std::ios::app);
    }
    else
    {
        fileId = FileDescriptorManager::openFile(filename, std::ios::binary | std::ios::out);
    }

    if(!fileId.has_value())
    {
        defaultLogger.log(LogType::WARNING, "(FileOpener) Unable to open \"{}\". Pushing zero to stack.", filename);
    }
    else
    {
        defaultLogger.log(LogType::INFO, "(FileOpener) Opened \"{}\". fileID: {}, appendMode: {}.", filename, fileId.value(), m_appendMode);
    }
    current->stackPtr->push( static_cast<var_t>(fileId.value_or(0)) );

    return Cable::work(current, currentVector);
}