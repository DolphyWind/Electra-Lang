// /**
// MIT License

// Copyright (c) 2023 Yunus Emre Aydın

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// */

// #include <Logger.hpp>

// Logger::Logger()
// {
//     std::time_t t = std::time(NULL);
//     std::tm* now = std::localtime(&t);
//     std::stringstream ss;
//     ss << "Log " << now->tm_mday << "_" << now->tm_mon + 1 << "_" << now->tm_year + 1900 << "_" << now->tm_hour << "_" << now->tm_min << "_" << now->tm_sec << ".log";
//     m_filename = ss.str();
// }

// template<typename T>
// void Logger::parseVariadic(std::vector<std::wstring> &out, T t)
// {
//     out.push_back(std::to_wstring(t));
// }

// template<typename T, typename... Args>
// void Logger::parseVariadic(std::vector<std::wstring> &out, T t, Args... args)
// {
//     out.push_back(std::to_wstring(t));
//     parseVariadic(out, args...);
// }


// template<typename... Args>
// void Logger::log(LogType logType, std::wstring message, Args... args)
// {
//     if(!loggingEnabled) return;
//     message = std::wstring(L"{}") + message;
    
//     std::vector<std::wstring> arguments;
//     parseVariadic(arguments, L"", args...);

//     if(!m_fileOpened)
//     {
//         m_writer.open(m_filename);
//         m_writer.imbue(std::locale(m_writer.getloc(), new std::codecvt_utf8<wchar_t>)); // For some reason using char_t gives an error
//         m_fileOpened = m_writer.good();
//         if(m_fileOpened) m_writer << std::fixed;
//     }

//     std::wstring logTypeStr;
//     switch (logType)
//     {
//     case LogType::WARNING:
//         logTypeStr = L"WARNING";
//         break;
//     case LogType::INFO:
//         logTypeStr = L"INFO";
//         break;
//     case LogType::ERROR:
//         logTypeStr = L"ERROR";
//         break;
//     default:
//         break;
//     }

//     for(auto& arg : arguments)
//     {
//         message = Global::replaceString(message, L"{}", arg);
//     }
    
//     // Write out logtype with item
//     m_writer << "[" << logTypeStr << "] " << message << L'\n';
// }

// Logger defaultLogger = Logger();