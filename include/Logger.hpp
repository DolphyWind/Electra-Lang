#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <GlobalFunctions.hpp>
#include <ctime>
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
    std::string replaceString(std::string& originalStr, const std::string& lookFor, const std::string& replaceWith);
    bool m_fileOpened = false;
public:
    Logger();
    ~Logger();

    bool loggingEnabled = true;
    void log(LogType logType, std::string message, std::vector<int> args = {});
};

extern Logger defaultLogger;