#include <string_conversions.hpp>


std::string std::to_string(const Direction &direction)
{
    switch (direction)
    {
    case Direction::EAST:
        return "east";
        break;
    case Direction::NORTHEAST:
        return "northeast";
        break;
    case Direction::NORTH:
        return "north";
        break;
    case Direction::NORTHWEST:
        return "northwest";
        break;
    case Direction::WEST:
        return "west";
        break;
    case Direction::SOUTHWEST:
        return "southwest";
        break;
    case Direction::SOUTH:
        return "south";
        break;
    case Direction::SOUTHEAST:
        return "southeast";
        break;
    case Direction::NONE:
    default:
        return "none";
        break;
    }
}

std::string std::to_string(const std::vector<Direction> &directions)
{
    std::string result = "{";
    for(std::size_t i = 0; i < directions.size(); i++)
    {
        result += std::to_string(directions[i]);
        if(i == directions.size() - 1) result += ", ";
    }
    result += "}";
    return result;
}

std::string std::to_string(const std::string &str)
{
    return str;
}