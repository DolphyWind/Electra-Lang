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
#include <limits>
#include <string>

class Camera
{
public:
    Camera();

    void setPos(int x, int y);
    void move(int dx, int dy);

    int getX() const;
    int getY() const;
    int getTerminalWidth() const;
    int getTerminalHeight() const;

    void setBounds(int minX, int minY, int maxX, int maxY);
    void update();
    void printChar(char c, int x, int y);
    void printString(const std::string& str, int x, int y);

    char getCharAt(int x, int y);

private:
    int m_x = 0;
    int m_y = 0;

    int m_minX = std::numeric_limits<decltype(m_minX)>::min();
    int m_minY = std::numeric_limits<decltype(m_minY)>::min();
    int m_maxX = std::numeric_limits<decltype(m_maxX)>::max();
    int m_maxY = std::numeric_limits<decltype(m_maxY)>::max();

    int m_termWidth = 0;
    int m_termHeight = 0;
};
