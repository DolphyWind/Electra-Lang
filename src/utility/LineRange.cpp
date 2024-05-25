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

#include <utility/LineRange.hpp>

LineRange::LineRange():
    m_begin(1), m_end(std::numeric_limits<std::size_t>::max())
{}

LineRange::LineRange(std::size_t begin, std::size_t end):
    m_begin(begin), m_end(end)
{}

bool LineRange::intersects(const LineRange& other) const
{
    if(other.getBegin() < m_begin) return other.intersects(*this);

    return (m_begin <= other.getBegin() && other.getBegin() < m_end);
}

std::size_t LineRange::getBegin() const
{
    return m_begin;
}

std::size_t LineRange::getEnd() const
{
    return m_end;
}

void LineRange::setBegin(std::size_t begin)
{
    m_begin = begin;
    m_begin = (m_begin == 0 ? 1 : m_begin);
    if(m_begin > m_end)
    {
        m_end = m_begin;
    }
}

void LineRange::setEnd(std::size_t end)
{
    m_end = end;
    if(m_end < m_begin)
    {
        m_begin = m_end;
    }
}

std::strong_ordering LineRange::operator<=>(const LineRange& other) const
{
    return m_begin <=> other.m_begin;
}
