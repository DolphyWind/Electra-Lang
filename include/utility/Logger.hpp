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

#pragma once
#include <iostream>
#include <fstream>
#include <utility/StringUtilities.hpp>
#include <utility/Global.hpp>

#ifdef ERROR
#undef ERROR
#endif

enum class LogType
{
    WARNING, 
    INFO,
    ERROR,
};

// A logger class for debugging purposes.
class Logger
{
public:
    Logger();
    bool loggingEnabled = false;

    template<typename... Args>
    void log(LogType logType, const std::string& message, Args&&... args);
    void log(LogType logType, const std::string& message);

    template<typename T, typename... Args>
    static std::string format(std::string& message, T&& t, Args&&... args);

    template<typename T>
    static std::string format(std::string& message, T&& t);

    static std::string_view logTypeToStr(LogType logType);
private:
    std::string m_filename;
    std::ofstream m_writer;
    bool m_fileOpened = false;
};

template<typename... Args>
void Logger::log(LogType logType, const std::string& message, Args&&... args)
{
    if(!loggingEnabled) return;

    if(!m_fileOpened)
    {
        m_writer.open(m_filename);
        m_fileOpened = !m_writer.fail();
        if(!m_fileOpened)
        {
            std::cerr << "Error: Cannot create log file." << std::endl;
            Global::safe_exit(1);
        }
        m_writer << std::fixed << std::boolalpha;
    }

    std::string mutableMessage = message;
    m_writer << '[' << logTypeToStr(logType) << "] " << format(mutableMessage, args...) << '\n';
}

template<typename T, typename... Args>
std::string Logger::format(std::string& message, T&& t, Args&&... args)
{
    constexpr std::string_view curly_braces = "{}";
    std::size_t pos = message.find(curly_braces);
    message.replace(pos, curly_braces.size(), sutil::to_string(t));

    return format(message, std::forward<Args>(args)...);
}

template<typename T>
std::string Logger::format(std::string& message, T&& t)
{
    constexpr std::string_view curly_braces = "{}";
    std::size_t pos = message.find(curly_braces);
    message.replace(pos, curly_braces.size(), sutil::to_string(t));

    return message;
}

extern Logger defaultLogger;
