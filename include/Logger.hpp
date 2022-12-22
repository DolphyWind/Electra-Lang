#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

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
public:
    Logger(const std::string& filename);
    ~Logger();

    void log(LogType logType, std::string message);
};