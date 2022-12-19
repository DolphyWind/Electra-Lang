#include <direction.hpp>

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