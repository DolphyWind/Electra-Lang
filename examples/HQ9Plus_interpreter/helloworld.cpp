#include "../../include/ComponentInformation.hpp"
#include "../../include/Current.hpp"
#include "../../include/Direction.hpp"
#include <iostream>
//g++ helloworld.cpp -fPIC -shared -o libhelloworld.so

extern "C"
{

void load(ComponentInformation& c)
{
    c.symbol = U'η';
    c.directions = {Direction::EAST, Direction::WEST};
    c.componentType = ComponentInformation::ComponentType::CLONING;
}

bool work(std::vector<std::stack<var_t>>& stacks, Current::Ptr currentPtr, std::vector<Current::Ptr>& currentVector)
{
    std::cout << "hello world\n";
    return true;
}

}
