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