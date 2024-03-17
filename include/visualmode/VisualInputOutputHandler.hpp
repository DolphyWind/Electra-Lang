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

#pragma once
#include <string>
#include <unordered_map>

#include <Direction.hpp>
#include <visualmode/Camera.hpp>
#include <visualmode/curses.hpp>

class VisualInputOutputHandler
{
public:
    VisualInputOutputHandler(Camera& cam, const Position& cursorPos);

    void print(char c, attr_t attrs=A_NORMAL);
    void print(char32_t c32, attr_t attrs=A_NORMAL);
    void print(const std::string& str, attr_t attrs=A_NORMAL);
    void print(const std::u32string& str, attr_t attrs=A_NORMAL);

    void update();
    void setCursorPosition(const Position& newCursorPos);
private:
    Camera& m_camera;
    Position m_cursorPosition;

    struct Character
    {
        char32_t chr;
        attr_t attr;
    };

    std::unordered_map<Position, Character, PositionHash> m_printedChars;
    void updatePos(char c);
};