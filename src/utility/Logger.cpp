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

#include <sstream>

#include <utility/Logger.hpp>

Logger::Logger()
{
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    std::stringstream ss;
    ss << "Log " << now->tm_mday << "_" << now->tm_mon + 1 << "_" << now->tm_year + 1900 << "_" << now->tm_hour << "_" << now->tm_min << "_" << now->tm_sec << ".log";
    m_filename = ss.str();
}

std::string_view Logger::logTypeToStr(LogType logType)
{
    switch (logType)
    {
        case LogType::WARNING:
            return "WARNING";
        case LogType::INFO:
            return "INFO";
        case LogType::ERROR:
            return "ERROR";
    }

    return "";
}

void Logger::log(LogType logType, const std::string& message)
{
    if(!loggingEnabled)
    {
        return;
    }

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

    m_writer << '[' << logTypeToStr(logType) << "] " << message << '\n';
}

Logger defaultLogger = Logger();
