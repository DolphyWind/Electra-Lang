#include "Logger.hpp"

Logger::Logger()
{
    std::time_t t = std::time(NULL);
    std::tm* now = std::localtime(&t);
    std::stringstream ss;
    ss << "Log " << now->tm_mday << "_" << now->tm_mon + 1 << "_" << now->tm_year + 1900 << "_" << now->tm_hour << "_" << now->tm_min << "_" << now->tm_sec << ".log";
    m_filename = ss.str();
}

Logger::~Logger()
{
    if(m_fileOpened)
        m_writer.close();
}

void Logger::log(LogType logType, std::string message, std::vector<int> args)
{
    if(!loggingEnabled) return;
    
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

    for(auto& arg : args)
    {
        message = replaceString(message, "{}", std::to_string(arg));
    }
    
    // Write out logtype with item
    m_writer << "[" << logTypeStr << "] " << message << '\n';
}

std::string Logger::replaceString(std::string& originalStr, const std::string& lookFor, const std::string& replaceWith)
{
    std::size_t pos = originalStr.find(lookFor);
    if(pos == std::string::npos)
        return originalStr;
    
    return originalStr.replace(pos, lookFor.length(), replaceWith);
}

Logger defaultLogger = Logger();