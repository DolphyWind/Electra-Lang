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

#include <visualmode/Camera.hpp>
#include <visualmode/curses.hpp>

Camera::Camera()
{
    update();
}

void Camera::setPos(int x, int y)
{
    if(x < m_minX)
    {
        x = m_minX;
    }
    if(y < m_minY)
    {
        y = m_minY;
    }
    if(x > m_maxX)
    {
        x = m_maxX;
    }
    if(y > m_maxY)
    {
        y = m_maxY;
    }

    m_x = x;
    m_y = y;
}

void Camera::move(int dx, int dy)
{
    return setPos(m_x + dx, m_y + dy);
}

int Camera::getX() const
{
    return m_x;
}

int Camera::getY() const
{
    return m_y;
}

int Camera::getTerminalWidth() const
{
    return m_termWidth;
}

int Camera::getTerminalHeight() const
{
    return m_termHeight;
}

void Camera::setBounds(int minX, int minY, int maxX, int maxY)
{
    if(maxY < minY)
    {
        maxY = minY;
    }
    if(maxX < minX)
    {
        maxX = minX;
    }

    m_minX = minX;
    m_minY = minY;
    m_maxX = maxX;
    m_maxY = maxY;
}

void Camera::update()
{
    getmaxyx(stdscr, m_termHeight, m_termWidth);
}

void Camera::printChar(char c, int x, int y)
{
    int x_on_camera = x - getX();
    int y_on_camera = y - getY();

    if(x_on_camera < 0 || y_on_camera < 0 || x_on_camera >= m_termWidth || y_on_camera >= m_termHeight)
    {
        return;
    }

    mvaddch(y_on_camera, x_on_camera, c);
}

void Camera::printString(const std::string& str, int x, int y)
{
    for(int i = 0; const auto& c : str)
    {
        printChar(c, x+i, y);
        ++i;
    }
}

char Camera::getCharAt(int x, int y)
{
    return static_cast<char>(mvinch(y - getY(), x - getX()) & A_CHARTEXT);
}