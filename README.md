# Electra-Lang
Small esolang inspired by AsciiDots. Uses instruction pointers that acts like currents in electricity.

# How Electra works?

Electra has generators and components. Generators generate currents and components interperate currents that came through them. Electra has two types defined. One of them is `var_t` (defined to be double) and the other one is `char_t` (defined to be char). Electra uses a single `std::stack<var_t>` for memory management.

## **Currents**
Currents are instruction pointers in electra. They call `work() `function of the component that they are on. A component's `work()` function returns a boolean value. If it is false current gets killed.

## **Generators (<, >, ^, v)**
Generators generate currents at the beginning of the program and become unused after that. They generate current based on their ascii character (> generates a current to the east, < generates a current to the west etc.)

## **Components**
Components are the elements that gives electra its functionality. Each component has its own job and can generate or remove existing currents. Each component except portals, inherit from Cable class which inherits from Component class (Portals directly inherit from Component class). And Cable class always calls `Component::work()` and immidiately returns false if it returns false thus kills the current. `Component::work()` checks the current's direction and component's supported directions and returns true if component supports a current coming from that direction, returns false if not. 

### **Cables (-, |, +, X, \*, \\, /)**
Cables are the simplest components of the electra and every component except portals inherits from them. Their job is actually clone currents to make them flow correctly if they are multi-directional. 

For example:

    >-----+-
          |

The regular four way cable (+) has a current that is coming from west heading to east. It will create 2 more copies of that current with directions north and south. The current with direction north will get killed in the next iteration. Cables clone and support currents based on their ascii value.

#### **Cable Types**
>**Horizontal Cable (-):** Supports east and west directions. Simple cable for moving current horizontally.

>**Vertical Cable (|):** Supports north and south directions. Simple cable for moving current vertically.

>**Right Diagonal Cable (/):** Supports northeast and southwest directions. Simple cable for moving current diagonally.

>**Left Diagonal Cable (\\):** Supports northwest and southeast directions. Simple cable for moving current diagonally.

>**Regular Four Way Cable (+):** Supports east, west, north and south directions. Can be used to change direction of a current or clone it.

>**Diagonal Four Way Cable (X):** Supports northeast, northwest, southeast and southwest directions. Can be used to change direction of a current or clone it.

>**Eight Way Cable (\*):** Supports all directions. Can be used to change direction of a current or clone it.

### **Printers (N, P)**
Printers lets electra print out the variables in the stack. They inherit from Cable class and return false if `Cable::work()` returns false.

#### **Printer Types**
>**Number Printer (N):** Supports east, west, southeast, southwest, northeast and northwest direction. Pops the top value off the stack and prints it as number. If the stack is empty it does nothing.

>**Character Printer (P):** Supports north, east, west, northeast, northwest and southwest directions. Pops the top value off the stack, converts it to char_t and prints it as a character. If the stack is empty it does nothing.

### **Arithmetical Units (A, S, M, Q, %)**
Arithmetical units lets electra do arithmetical calculations. They inherit from Cable class and return false if `Cable::work()` returns false.

#### **Arithmetical Unit Types**
>**Adder (A):** Supports north, southeast and southwest directions. Pops two values off the stack and pushes first+second back. If there is at least no two values on the stack, it does nothing.

>**Subtracter (S):** Supports north, south, southwest and northeast directions. Pops two values off the stack and pushes first-second back. If there is at least no two values on the stack, it does nothing.

>**Multiplier (M):** Supports east, west, southeast, southwest, northeast and northwest directions. Pops two values off the stack and pushes first*second back. If there is at least no two values on the stack, it does nothing.

>**Divider (Q):** Supports north, south, east, west and southeast directions. Pops two values off the stack and pushes first/second back. If there is at least no two values on the stack, it does nothing.

>**Modder (%):** Supports northeast and southwest directions. Pops two values off the stack and pushes `std::fmod(first, second)` back. If there is at least no two values on the stack, it does nothing.

#### **Constant Adders (I, D)**
Constant adders adds a constant value to the top value of the stack. They inherit from Cable class and return false if `Cable::work()` returns false.

>**Increaser (I):** Supports north and south directions. Pops the top value off the stack and adds one to it. Then pushes the result back. It does nothing if the stack is empty.

>**Decreaser (D):** Supports east, west, north, south southwest and northwest directions. Pops the top value off the stack and subtracts one from it. Then pushes the result back. It does nothing if the stack is empty.



**TODO:** Add explanation for each component and portals.

**TODO:** Add example codes for truth-machine, FizzBuzz, Hello World!
