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
#include <components/Cable.hpp>
#include <string>

// Holds flown currents still until it is activated. To activate a key, a current has to touch it from its activator directions.
class Key : public Cable
{
public:
    Key(const std::vector<Direction>& directions, const std::vector<Direction>& activatorDirections, std::vector<std::u32string>& sourceCode, char32_t transformTo);
    ~Key() override = default;

    bool work(Current::Ptr current, std::vector<Current::Ptr>& currentVector) override;
private:
    std::vector<Direction> m_activatorDirections;
    std::vector<std::u32string>& m_sourceCode;
    char32_t m_transformTo;
};