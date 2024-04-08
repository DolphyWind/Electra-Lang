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

#include <iostream>

#include <visualmode/VisualInputOutputHandler.hpp>
#include <visualmode/VisualModeManager.hpp>
#include <visualmode/curses.hpp>
#include <Electra.hpp>

VisualModeManager::VisualModeManager(Electra& interpreter):
    m_vioh(m_defaultCamera, {0, 0}), m_interpreter(interpreter)
{}

VisualModeManager::~VisualModeManager()
{
    if(m_setup)
    {
        endwin();
    }
}

VisualInputOutputHandler& VisualModeManager::getVIOH()
{
    return m_vioh;
}

const VisualInputOutputHandler& VisualModeManager::getVIOH() const
{
    return m_vioh;
}

void VisualModeManager::setup()
{
    m_setup = true;
    initscr();
    raw();
    curs_set(0);
    keypad(stdscr, true);
    noecho();
    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
    }
    else
    {
        // error here
    }
    timeout(30 * m_visualModeSpeed - 1);
}

bool VisualModeManager::isSetup() const
{
    return m_setup;
}

void VisualModeManager::deduceScreenParameters()
{
    if(!isSetup()) return;

    int longestLine = 0;
    for(auto& line : m_interpreter.getSourceCode())
    {
        if(line.length() > longestLine)
        {
            longestLine = static_cast<int>(line.length());
        }
    }
    m_defaultCamera.setBounds(-50, -30, longestLine - m_defaultCamera.getTerminalWidth(), static_cast<int>(m_interpreter.getSourceCode().size()) - m_defaultCamera.getTerminalHeight());
    m_vioh.setCursorPosition({0, static_cast<int>(m_interpreter.getSourceCode().size())});
    m_vioh.print("OUTPUT\n", A_BOLD);
}

VisualModeState VisualModeManager::update()
{
    if(!isSetup()) return m_state;
    if(m_state == VisualModeState::STEP)
    {
        m_state = VisualModeState::PAUSED;
    }

    m_defaultCamera.update();
    clear();
    for(int y = 0; auto& line : m_interpreter.getSourceCode())
    {
        m_defaultCamera.printString(line, 0, y);
        ++y;
    }
    attron(COLOR_PAIR(1));
    attron(A_BOLD);
    for(auto& current : m_interpreter.getCurrents())
    {
        int x = current->getPosition().x;
        int y = current->getPosition().y;
        m_defaultCamera.printChar(m_defaultCamera.getCharAt(x, y), x, y);
    }
    attroff(A_BOLD);
    attroff(COLOR_PAIR(1));

    m_vioh.update();

    refresh();
    m_previousChar = m_currentChar;
    m_currentChar = getch();

    switch (m_state)
    {
        case VisualModeState::NORMAL:
        {
            switch(m_currentChar)
            {
                case 'p':
                case 'P':
                {
                    if(m_previousChar != 'p' && m_previousChar != 'P')
                    {
                        m_state = VisualModeState::PAUSED;
                    }
                    break;
                }
                default:
                {
                    // std::cerr << (int)m_currentChar << '\n';
                    break;
                }
            }
            break;
        }
        case VisualModeState::PAUSED:
        {
            switch (m_currentChar)
            {
                case 's':
                case 'S':
                    m_state = VisualModeState::STEP;
                    break;
                case 'p':
                case 'P':
                {
                    if(m_previousChar != 'p' && m_previousChar != 'P')
                    {
                        m_state = VisualModeState::NORMAL;
                    }
                    break;
                }
            }
            break;
        }
        case VisualModeState::INPUT:
            break;
        case VisualModeState::STEP:
        case VisualModeState::EXIT:
            break;
    }

    if(m_state == VisualModeState::INPUT)
    {
        return m_state;
    }

    switch(m_currentChar)
    {
        case 261:
            m_defaultCamera.move(camSpeedX, 0);
            break;
        case 260:
            m_defaultCamera.move(-camSpeedX, 0);
            break;
        case 259:
            m_defaultCamera.move(0, -camSpeedY);
            break;
        case 258:
            m_defaultCamera.move(0, camSpeedY);
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        {
            m_visualModeSpeed = m_currentChar - '0';
            timeout(m_visualModeSpeed * 30 - 10);
            break;
        }
        case 'q':
        case 'Q':
            m_state = VisualModeState::EXIT;
            break;
    }

    return m_state;
}

