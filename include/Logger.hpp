#pragma once
#include <codecvt>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <Global.hpp>
#include <ctime>
#include <sstream>
#include <string_conversions.hpp>

enum class LogType
{
    WARNING, 
    INFO,
    ERROR,
};

// A logger class for debugging purposes.
class Logger
{
private:
    std::string m_filename;
    std::wofstream m_writer;
    std::wstring replaceString(std::wstring& originalStr, const std::wstring& lookFor, const std::wstring& replaceWith);
    bool m_fileOpened = false;

    template<typename T>
    void parseVariadic(std::vector<std::wstring> &output, T t);

    template<typename T, typename... Args>
    void parseVariadic(std::vector<std::wstring> &output, T t, Args... args);
public:
    Logger();
    bool loggingEnabled = false;

    /// @brief Logs the given string with given LogType into a file with formatting.
    /// 
    /// @param logType Type of log. Can be one from WARNING, INFO and ERROR.
    /// @param message Message you want to log.
    /// @param args Arguments that will be formatted
    template<typename... Args>
    void log(LogType logType, std::wstring message, Args... args);
};

template<typename T>
void Logger::parseVariadic(std::vector<std::wstring> &out, T t)
{
    out.push_back(std::to_wstring(t));
}

template<typename T, typename... Args>
void Logger::parseVariadic(std::vector<std::wstring> &out, T t, Args... args)
{
    out.push_back(std::to_wstring(t));
    parseVariadic(out, args...);
}


template<typename... Args>
void Logger::log(LogType logType, std::wstring message, Args... args)
{
    if(!loggingEnabled) return;
    message = std::wstring(L"{}") + message;
    
    std::vector<std::wstring> arguments;
    parseVariadic(arguments, L"", args...);

    if(!m_fileOpened)
    {
        m_writer.open(m_filename);
        m_writer.imbue(std::locale(m_writer.getloc(), new std::codecvt_utf8<wchar_t>)); // For some reason using char_t gives an error
        m_fileOpened = m_writer.good();
    }

    std::wstring logTypeStr;
    switch (logType)
    {
    case LogType::WARNING:
        logTypeStr = L"WARNING";
        break;
    case LogType::INFO:
        logTypeStr = L"INFO";
        break;
    case LogType::ERROR:
        logTypeStr = L"ERROR";
        break;
    default:
        break;
    }

    for(auto& arg : arguments)
    {
        message = replaceString(message, L"{}", arg);
    }
    
    // Write out logtype with item
    m_writer << "[" << logTypeStr << "] " << message << L'\n';
}

extern Logger defaultLogger;