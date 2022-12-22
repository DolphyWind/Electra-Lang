#include "Logger.hpp"

Logger::Logger(const std::string& filename): m_filename(filename)
{
    m_writer.open(m_filename);
}

Logger::~Logger()
{
    m_writer.close();
}

void Logger::log(LogType logType, std::string message)
{   
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
    
    // Write out logtype with item
    m_writer << "[" << logTypeStr << "] " << message << "\n";
}