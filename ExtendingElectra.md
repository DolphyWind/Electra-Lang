## Extending Electra Using C++
You can add your own components to Electra using C++ shared libraries, also referred as packages.
When the Electra interpreter loads a package, it looks for a single function:
- `void load(std::vector<ComponentInformation>&)`

#### Load Function
The purpose of the `load` function is simple; It takes a reference to a vector of ComponentInformation
objects and populates it with custom components. Let's look at an example:
```cpp
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
```

- The `symbol` field is the Unicode character representation of the component. It overwrites
any component with the same symbol.
- The `directions` field is a list of supported directions.
- The `componentType` field specifies the component's type. The `componentType` can take
two values: `ComponentType::CLONING` or `ComponentType::NON_CLONING`. `NON_CLONING` components
do not clone the current after they've done their job, like portals. And as you may guess,
`CLONING` components do clone the current after they've done their job like any other component in Electra.
- The `workFunc` field is the function that gets triggered when a current touches it. If it returns false
the current dies. Its signature should be, `bool(std::vector<std::stack<var_t>>&, Current::Ptr&, std::vector<Current::Ptr>&)`

### Full Example
An example program that uses packages can be found [here](https://github.com/DolphyWind/Electra-Lang/tree/master/examples/HQ9Plus_interpreter).
