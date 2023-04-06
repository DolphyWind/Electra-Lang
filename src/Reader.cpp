#include "Cable.hpp"
#include "Logger.hpp"
#include <Reader.hpp>
#include <string>

bool Reader::work(CurrentPtr current, std::vector<CurrentPtr> *currentVector)
{
    if(!Cable::work(current, currentVector))
        return false;
    
    if(m_getInputAsChar)
    {
        char_t c;
        std::wcin >> c;
        current->stackPtr->push(c);
        defaultLogger.log(LogType::INFO, L"(Reader) Read {} from user and pushed onto stack.", std::wstring(1, c));
    }
    else
    {
        var_t v;
        std::wcin >> v;
        current->stackPtr->push(v);
        defaultLogger.log(LogType::INFO, L"(Reader) Read {} from user and pushed onto stack.", v);
    }
    return true;
}