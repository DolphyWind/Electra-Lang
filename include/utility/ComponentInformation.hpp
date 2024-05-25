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
#include <functional>
#include <stack>
#include <vector>

#include "../Direction.hpp"
#include "../utility/Global.hpp"
#include "../Current.hpp"

typedef std::function<bool(Current::Ptr& current, std::vector<Current::Ptr>&)> WorkFunctionType;
typedef std::function<bool(std::vector<std::stack<var_t>>&, Current::Ptr& current, std::vector<Current::Ptr>&)> WorkFunctionWithStacksType;

enum class ComponentType
{
    CLONING,
    NON_CLONING
};

struct ComponentInformation
{
    char32_t symbol = U'\0';
    std::vector<Direction> directions{};
    ComponentType componentType{ComponentType::CLONING};
    WorkFunctionWithStacksType workFunc;
};
