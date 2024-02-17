#include "../../include/ComponentInformation.hpp"
#include "../../include/Current.hpp"
#include "../../include/Direction.hpp"
#include <iostream>
// g++ 99bottles.cpp -fPIC -shared -o lib99bottles.so

extern "C"
{

void load(ComponentInformation& c)
{
    c.symbol = U'9';
    c.directions = {Direction::EAST, Direction::WEST};
    c.componentType = ComponentInformation::ComponentType::CLONING;
}

bool work(std::vector<std::stack<var_t>>& stacks, Current::Ptr currentPtr, std::vector<Current::Ptr>& currentVector)
{

    for(int i = 99; i > 1; --i)
    {
        char c = 's';
        if(i == 2) c = '\0';
        std::cout << i << " bottles of beer on the wall,\n" << i << " bottles of beer.\n";
        std::cout << "Take one down and pass it around,\n" << (i-1) << " bottle" << c << " of beer on the wall.\n\n";
    }

    std::cout << "1 bottle of beer on the wall,\n1 bottle of beer\n";
    std::cout << "Take one down and pass it around,\nNo bottles of beer on the wall\n";

    return true;
}

}
