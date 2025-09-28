#include "../../include/utility/ComponentInformation.hpp"
#include "../../include/Current.hpp"
#include "../../include/Direction.hpp"
#include <iostream>
#include <vector>
// g++ hq9plus.cpp -fPIC -shared -o libhq9plus.so

extern "C"
{

bool work_9(std::vector<std::stack<var_t>>& stacks, Current::Ptr& currentPtr, std::vector<Current::Ptr>& currentVector)
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

bool work_h(std::vector<std::stack<var_t>>& stacks, Current::Ptr& currentPtr, std::vector<Current::Ptr>& currentVector)
{
    std::cout << "hello world\n";
    return true;
}

void load(std::vector<ComponentInformation>& components)
{
    components.push_back({
        .symbol = U'9',
        .directions = {Direction::EAST, Direction::WEST},
        .componentType = ComponentType::CLONING,
        .workFunc = work_9
    });
    components.push_back({
        .symbol = U'η',
        .directions = {Direction::EAST, Direction::WEST},
        .componentType = ComponentType::CLONING,
        .workFunc = work_h
    });
}

}
