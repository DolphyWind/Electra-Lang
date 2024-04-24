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

#include <thirdparty/utfcpp/utf8.h>
#include <visualmode/VisualInputOutputHandler.hpp>

VisualInputOutputHandler::VisualInputOutputHandler(Camera& cam, const Position& cursorPosition):
    std::ostream(this), m_camera(cam), m_cursorPosition(cursorPosition)
{}

void VisualInputOutputHandler::print(char c, attr_t attrs)
{
    if(c == 0)
    {
        return;
    }
    attron(attrs);
    m_camera.printChar(c, m_cursorPosition.x, m_cursorPosition.y);
    attroff(attrs);
    m_printedChars[m_cursorPosition] = {static_cast<char32_t>(c), attrs};
    updatePos(c);
}

void VisualInputOutputHandler::print(char32_t c32, attr_t attrs)
{
    if(c32 == 0)
    {
        return;
    }
    attron(attrs);
    m_camera.printChar(c32, m_cursorPosition.x, m_cursorPosition.y);
    attroff(attrs);
    m_printedChars[m_cursorPosition] = {c32, attrs};
    updatePos(static_cast<char>(c32));
}

void VisualInputOutputHandler::print(const std::string& str, attr_t attrs)
{
    for(const auto& c : str)
    {
        print(c, attrs);
    }
}

void VisualInputOutputHandler::print(const std::u32string& str, attr_t attrs)
{
    for(const auto& c : str)
    {
        print(c, attrs);
    }
}

std::string VisualInputOutputHandler::take_input()
{
    echo();
    static constexpr std::size_t buff_size = 4096;
    char buff[buff_size];
    getstr(buff);
    std::string input(buff);
    std::size_t eof_pos = input.find(4);

    if(eof_pos != std::string::npos)
    {
        input = input.substr(0, eof_pos);
    }
    print(input);
    print('\n');

    noecho();
    return input;
}

void VisualInputOutputHandler::update()
{
    for(auto&[pos, c] : m_printedChars)
    {
        attron(c.attr);
        if(c.chr < 256)
        {
            m_camera.printChar(static_cast<char>(c.chr), pos.x, pos.y);
            attroff(c.attr);
            continue;
        }

        m_camera.printChar(c.chr, pos.x, pos.y);
        attroff(c.attr);
    }
}

void VisualInputOutputHandler::setCursorPosition(const Position& newCursorPos)
{
    m_cursorPosition = newCursorPos;
}

void VisualInputOutputHandler::updatePos(char c)
{
    if(c == '\n')
    {
        ++m_cursorPosition.y;
        m_cursorPosition.x = 0;
        return;
    }
    if(c == '\r')
    {
        m_cursorPosition.x = 0;
        return;
    }
    ++m_cursorPosition.x;
}
