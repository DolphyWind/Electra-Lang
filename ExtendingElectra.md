## Extending Electra Using C++
You can add your own components to electra using C++ shared libraries.
When the electra interpreter loads a shared library, it looks for two functions:
- `void load(ComponentInformation&)`
- `bool work(std::vector<std::stack<double>>&, Current::Ptr, std::vector<Current::Ptr>&)`

#### Load Function
The purpose of the `load` function is simple; It takes a reference to a ComponentInformation
object and modifies it. Let's look at an example:
```cpp
void load(ComponentInformation& c)
{
    c.symbol = U'9';
    c.directions = {Direction::EAST, Direction::WEST};
    c.componentType = ComponentInformation::ComponentType::CLONING;
}
```

- The `symbol` field is the unicode character representation of the component. It overwrites
any component with the same symbol.
- The `directions` field is a list of supported directions.
- The `componentType` field specifies the component's type. The `componentType` can take
two values: `ComponentInformation::ComponentType::CLONING` or `ComponentInformation::ComponentType::NON_CLONING`.
`NON_CLONING` components do not clone the current after they've done their job, like portals.
And as you may guess, `CLONING` components do clone the current after they've done their job like any other component in electra.

#### Work Function
The `work` function is the function specifies the actual job of the component. It has three parameters
- The first parameter is a reference to the memory of electra.
- The second parameter is a shared pointer to the current that triggered the component
- The third parameter is a vector of currents, if you want to create new currents, you can do so
by pushing new currents to this vector.

If the `work` function returns false, the current gets killed and no cloning occurs.
(Note: If you manually push some currents to the last parameter, they'll still be created)

### Full Example
Let's look at an example to better understand how you can create a custom component:
```cpp
#include "ComponentInformation.hpp"
#include "Current.hpp"
#include "Direction.hpp"
#include <iostream>
//g++ helloworld.cpp -fPIC -shared -o libhelloworld.so

extern "C"
{
    
// We create a custom component. It supports west and east directions and '5' is its symbol.
// It also clones currents after it's done its work
void load(ComponentInformation& c)
{
    c.symbol = U'5';
    c.directions = {Direction::EAST, Direction::WEST};
    c.componentType = ComponentInformation::ComponentType::CLONING;
}

// The component just prints hello world to the screen
bool work(std::vector<std::stack<var_t>>& stacks, Current::Ptr currentPtr, std::vector<Current::Ptr>& currentVector)
{
    std::cout << "hello world\n";
    return true;
}

}
```
