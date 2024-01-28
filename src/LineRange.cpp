#include "LineRange.hpp"

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
    if(m_begin > m_end) m_end = m_begin;
}

void LineRange::setEnd(std::size_t end)
{
    m_end = end;
    if(m_end < m_begin) m_begin = m_end;
}

std::strong_ordering LineRange::operator<=>(const LineRange& other) const
{
    return m_begin <=> other.m_begin;
}