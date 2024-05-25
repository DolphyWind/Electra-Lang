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

#include <utility/FileDescriptorManager.hpp>

std::unordered_map<std::size_t, std::fstream> FileDescriptorManager::fstreamMap{};

std::optional<std::size_t> FileDescriptorManager::openFile(const std::string& name, std::ios_base::openmode openmode)
{
    static std::size_t id = 1;
    fstreamMap[id].open(name, openmode);

    if(fstreamMap[id].fail())
    {
        return std::nullopt;
    }

    return id++;
}

bool FileDescriptorManager::write(std::size_t id, const std::string& msg)
{
    if(!fstreamMap.contains(id) || fstreamMap[id].fail())
    {
        return false;
    }

    fstreamMap[id] << msg;
    return true;
}

bool FileDescriptorManager::close(std::size_t id)
{
    if(!fstreamMap.contains(id) || fstreamMap[id].fail())
    {
        return false;
    }

    fstreamMap[id].close();
    return true;
}
