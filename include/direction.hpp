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
#include <iostream>
#include <vector>

enum class Direction
{
    EAST = 0,
    NORTHEAST = 1,
    NORTH = 2,
    NORTHWEST = 3,
    WEST = 4,
    SOUTHWEST = 5,
    SOUTH = 6,
    SOUTHEAST = 7,
    NONE = 8,
};

struct Position
{
    int x = 0;
    int y = 0;
    
    Position(int _x = 0, int _y = 0): x(_x), y(_y) {};
    bool operator==(Position& right);
    bool operator!=(Position& right);
    Position operator+(const Position &right);
};

// Converts direction to position
Position directionToPosition(const Direction &direction);

// Inverts the given direction
Direction invertDirection(const Direction &direction);

// Converts any number to vector direction
std::vector<Direction> bin2dir(std::size_t num);