#pragma once

enum class Direction
{
    EAST = 0,
    NORTHEAST = 1,
    NORTH = 2,
    NORTHWEST = 3,
    WEST = 4,
    SOUTHWEST = 5,
    SOUTH = 6,
    SOUTHEAST = 7
};

struct Position
{
    int x = 0;
    int y = 0;
};

Position directionToPosition(Direction direction);