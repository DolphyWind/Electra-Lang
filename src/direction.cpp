#include <direction.hpp>

bool Position::operator==(Position& right)
{
    return this->x == right.x && this->y == right.y;
}

bool Position::operator!=(Position& right)
{
    return !operator==(right);
}

Position directionToPosition(Direction direction)
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
    }
}

Direction invertDirection(Direction direction)
{
    int dirAsInt = (int)direction;
    return (Direction)((dirAsInt + 4) % 8);
}