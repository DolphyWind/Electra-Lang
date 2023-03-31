#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <GlobalFunctions.hpp>
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
    std::ofstream m_writer;
    std::string replaceString(std::string& originalStr, const std::string& lookFor, const std::string& replaceWith);
    bool m_fileOpened = false;

    template<typename T>
    void parseVariadic(std::vector<std::string> &output, T t);

    template<typename T, typename... Args>
    void parseVariadic(std::vector<std::string> &output, T t, Args... args);
public:
    Logger();
    ~Logger();

    bool loggingEnabled = false;

    template<typename... Args>
    void log(LogType logType, std::string message, Args... args);
};

template<typename T>
void Logger::parseVariadic(std::vector<std::string> &out, T t)
{
    out.push_back(std::to_string(t));
}

template<typename T, typename... Args>
void Logger::parseVariadic(std::vector<std::string> &out, T t, Args... args)
{
    out.push_back(std::to_string(t));
    parseVariadic(out, args...);
}


template<typename... Args>
void Logger::log(LogType logType, std::string message, Args... args)
{
    if(!loggingEnabled) return;
    message = std::string("{}") + message;
    
    std::vector<std::string> arguments;
    parseVariadic(arguments, "", args...);

    if(!m_fileOpened)
    {
        m_writer.open(m_filename);
        m_fileOpened = m_writer.good();
    }

    std::string logTypeStr;
    switch (logType)
    {
    case LogType::WARNING:
        logTypeStr = "WARNING";
        break;
    case LogType::INFO:
        logTypeStr = "INFO";
        break;
    case LogType::ERROR:
        logTypeStr = "ERROR";
        break;
    default:
        break;
    }

    for(auto& arg : arguments)
    {
        message = replaceString(message, "{}", arg);
    }
    
    // Write out logtype with item
    m_writer << "[" << logTypeStr << "] " << message << '\n';
}

extern Logger defaultLogger;