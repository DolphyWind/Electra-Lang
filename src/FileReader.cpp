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
#include <fstream>
#include <sstream>

#include <FileReader.hpp>
#include <Logger.hpp>

FileReader::FileReader(const std::vector<Direction>& directions):
    Cable(directions)
{}

bool FileReader::work(Current::Ptr current, std::vector<Current::Ptr>& currentVector)
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

    std::ifstream ifs(filename, std::ios::binary);
    if(ifs.fail())
    {
        defaultLogger.log(LogType::WARNING, "(FileReader) Unable to open \"{}\". Pushing 0 to stack.", filename);
        current->stackPtr->push(0);
        return Cable::work(current, currentVector);
    }

    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    std::string fileContent_utf8 = ss.str();
    std::u32string fileContent;
    fileContent.reserve(fileContent_utf8.size());
    utf8::utf8to32(fileContent_utf8.begin(), fileContent_utf8.end(), std::back_inserter(fileContent));

    while(!fileContent.empty())
    {
        current->stackPtr->push(static_cast<var_t>( fileContent[fileContent.length() - 1] ));
        fileContent.pop_back();
    }
    defaultLogger.log(LogType::INFO, "(FileReader) Read \"{}\".", filename);

    return Cable::work(current, currentVector);
}
