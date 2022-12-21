#pragma once
#include <iostream>

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
};

struct Position
{
    int x = 0;
    int y = 0;
    
    Position(int _x = 0, int _y = 0): x(_x), y(_y) {};
    bool operator==(Position& right);
    bool operator!=(Position& right);
    Position operator+(Position &right);
};

Position directionToPosition(Direction direction);
Direction invertDirection(Direction direction);