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

#include <direction.hpp>

bool Position::operator==(Position& right)
{
    return this->x == right.x && this->y == right.y;
}

bool Position::operator!=(Position& right)
{
    return !operator==(right);
}

Position Position::operator+(const Position& right)
{
    return {this->x + right.x, this->y + right.y};
}

Position directionToPosition(const Direction &direction)
{
    // -1 on y coordinate mean up since the origin of the array is on the top left corner.

    switch (direction)
    {
    case Direction::EAST:
        return {1, 0};
        break;
    case Direction::NORTHEAST:
        return {1, -1};
        break;
    case Direction::NORTH:
        return {0, -1};
        break;
    case Direction::NORTHWEST:
        return {-1, -1};
        break;
    case Direction::WEST:
        return {-1, 0};
        break;
    case Direction::SOUTHWEST:
        return {-1, 1};
        break;
    case Direction::SOUTH:
        return {0, 1};
        break;
    case Direction::SOUTHEAST:
        return {1, 1};
        break;
    case Direction::NONE:
    default:
        return {0, 0};
        break;
    }
}

Direction invertDirection(const Direction &direction)
{
    if(direction == Direction::NONE) return Direction::NONE;
    int dirAsInt = (int)direction;
    return (Direction)((dirAsInt + 4) % 8);
}

std::vector<Direction> bin2dir(std::size_t num)
{
    std::vector<Direction> output;
    std::size_t index;
    while(num)
    {
        if(num & 0x1) output.push_back((Direction)index);
        num >>= 1;
        index ++;
    }
    return output;
}