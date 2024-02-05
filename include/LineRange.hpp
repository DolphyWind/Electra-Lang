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
#include <compare>

class LineRange
{
public:
    LineRange();
    explicit LineRange(std::size_t begin, std::size_t end=std::numeric_limits<std::size_t>::max());
    LineRange(const LineRange&) = default;
    LineRange(LineRange&&) = default;
    LineRange& operator=(const LineRange&) = default;
    LineRange& operator=(LineRange&&) = default;
    ~LineRange() = default;

    [[nodiscard]] bool intersects(const LineRange& other) const;
    [[nodiscard]] std::size_t getBegin() const;
    [[nodiscard]] std::size_t getEnd() const;
    void setBegin(std::size_t begin);
    void setEnd(std::size_t end);
    std::strong_ordering operator<=>(const LineRange& other) const;

private:
    std::size_t m_begin;
    std::size_t m_end;
};