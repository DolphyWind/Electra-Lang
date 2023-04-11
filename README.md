[![Linux Build](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Linux.yml/badge.svg)](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Linux.yml)  
[![Windows Build](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Windows.yml/badge.svg)](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Windows.yml)  
[![MacOS Build](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Mac.yml/badge.svg)](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Mac.yml)

# What is Electra?

Electra is an [esolang](https://esolangs.org/wiki/Esoteric_programming_language) inspired by [AsciiDots](https://esolangs.org/wiki/AsciiDots). It uses instruction pointers that acts like currents in electricity.  

# How to get electra?

If you are on Arch Linux or a Linux distrubution that is based on Arch Linux, you can download Electra using the [AUR](https://aur.archlinux.org). To download electra from AUR, install an AUR helper like `yay`. Then type the command below into the terminal to install Electra.

```bash
yay -S electra-git
```  
If you are on a Linux distrubution that is not Arch Linux based, or using completely different operating system. Currently the only option to get Electra running on your system is building Electra from source. To build Electra from source, open up a terminal and follow the steps below.

## Building on Unix-Like Operating Systems

If you are on a Unix-Like operating system such as Linux, MacOS, BSD etc. To build electra from source, use the commands down below.

```bash
# Clone the repository and cd into it
git clone https://github.com/DolphyWind/Electra-Lang.git
cd Electra-Lang
# Create a build directory
mkdir build
cd build
# Run cmake to generate build files
cmake .. 
# Build Electra with make.
make
# (Optional) Install Electra to your system
sudo make install
```

## Building on Windows

If you are on Windows, please install [Git for Windows](https://gitforwindows.org/), [Mingw-w64](https://www.mingw-w64.org/downloads/), [CMake](https://cmake.org/download/) and add them to your PATH. Building with Visual Studio is currently NOT supported. Also, please note that Windows build is a bit unstable and might not work in your system. It worked on my Windows 10 and Windows 11 machines but for some reason it doesn't work on virtual machines. To build electra on windows, follow the steps below.

```bash
# Clone the repository and cd into it
git clone https://github.com/DolphyWind/Electra-Lang.git
cd Electra-Lang
# Create a build directory
mkdir build
cd build
# Run cmake to generate build files with MinGW Configuration
cmake .. -G "MinGW Makefiles"
# Build Electra with make. If make gives an error, try it with mingw32-make or mingw64-make.
make
```

# How Electra works?

Electra has Currents, Generators and Components. Currents are instruction pointers that acts like the currents in electricity, Generators generate currents and Components interperate currents to make code function. Electra has two types defined. Electra uses multiple stacks of doubles for memory management. Electra also supports commenting your code in line and including other code files. To comment a portion of your code, encapsulate your comments with question marks ?like this?. To include other files in your code, use double quotes: "file.ec" x:y. This will include the lines in range from x to y (x-inclusive, y-exclusive). If you don't specify any lines electra will include whole file into your code. That operation replaces that line with corresponding file content so it has to be used with cauton.

## **Currents**
Currents are instruction pointers in Electra. They call `work()` function of the component that they are on. They hold a pointer to a stack and a component's `work()` function uses that stack if it does some stack operations. A `work()` function returns a boolean value. If it is false current gets killed.

## **Generators**
Generators generate currents at the beginning of the program and become unused after that. They generate current based on how they look like. To make looping easier, generators also lets current flowing on them. They support the direction in which they generate current and its opposite.

#### **Generator Types**
>**East Generator (>, →):** Generates a current with east direction.

>**West Generator (<, ←):** Generates a current with west direction.

>**North Generator (^, ↑):** Generates a current with north direction.

>**South Generator (v, ↓):** Generates a current with south direction.

>**Northeast Generator (↗):** Generates a current with northeast direction.

>**Northwest Generator (↖):** Generates a current with northwest direction.

>**Southeast Generator (↙):** Generates a current with southeast direction.

>**Southwest Generator (↘):** Generates a current with southwest direction.

>**Horizontal Bidirectional Generator (↔):** Generates two currents with east and west directions.

>**Vertical Bidirectional Generator (↕):** Generates two currents with north and south directions.

## **Components**
Components are the elements that gives Electra its functionality. Each component has its own job and can generate or kill existing currents. Each component except portals, inherit from Cable class which inherits from Component class (Portals directly inherit from Component class). And Cable class always calls `Component::work()` and immidiately returns false if it returns false thus kills the current. `Component::work()` checks the current's direction and component's supported directions and returns true if component supports a current coming from that direction, returns false otherwise. 

### **Cables**
Cables are the simplest components of the Electra and every component except portals inherits from them. Some cables also clone currents.

For example:

    >-----+-
          |

The regular four directional cable (+) has a current that is coming from west heading to east. It will create 2 more copies of that current with directions north and south. The current with direction north will get killed in the next iteration. Cables clone and support currents based on how they look like.

#### **Cable Types**
>**Horizontal Cable (-):** Supports east and west directions. Simple cable for flowing current horizontally.

>**Vertical Cable (|):** Supports north and south directions. Simple cable for flowing current vertically.

>**Right Diagonal Cable (/, ╱):** Supports northeast and southwest directions. Simple cable for flowing current diagonally.

>**Left Diagonal Cable (\\, ╲):** Supports northwest and southeast directions. Simple cable for flowing current diagonally.

>**Regular Four Directional Cable (+, ┼):** Supports east, west, north and south directions. Can be used to change direction of a current or clone it.

>**Diagonal Four Directional Cable (X, ╳):** Supports northeast, northwest, southeast and southwest directions. Can be used to change direction of a current or clone it.

>**Eight Directional Cable (\*, ✱):** Supports all directions. Can be used to change direction of a current or clone it.

>**East One Directional Cable (}):** Only lets current flowing to east direction.

>**West One Directional Cable ({):** Only lets current flowing to west direction.

>**North One Directional Cable (n):** Only lets current flowing to north direction.

>**South One Directional Cable (U):** Only lets current flowing to south direction.

>**Other Cables (╰, └, ╯, ┘, ╭, ┌, ┐, ╮, ├ ,┤ ,┬ ,┴):** These cables are not special they just have no name. They let current based on how they look like.

### **Printers**
Printers lets Electra print out the variables in the stack. They inherit from Cable class and return false if `Cable::work()` returns false.

#### **Printer Types**
>**Number Printer (N):** Supports east, west, southeast, southwest, northeast and northwest direction. Pops the top value off the current's stack and prints it as number. If the stack is empty it does nothing.

>**Character Printer (P):** Supports north, west, east, northeast, northwest and southwest directions. Pops the top value off the current's stack, converts it to char_t and prints it as a character. If the stack is empty it does nothing.

### **Arithmetical Units**
Arithmetical units lets Electra do arithmetical calculations. They inherit from Cable class and return false if `Cable::work()` returns false.

#### **Arithmetical Unit Types**
>**Adder (A):** Supports north, southeast and southwest directions. Pops two values off the stack and pushes first+second back. If there is at least no two values on the stack, it does nothing.

>**Subtracter (S):** Supports north, south, southwest and northeast directions. Pops two values off the stack and pushes first-second back. If there is at least no two values on the stack, it does nothing.

>**Multiplier (M):** Supports east, west, south, southeast, southwest, northeast and northwest directions. Pops two values off the stack and pushes first*second back. If there is at least no two values on the stack, it does nothing.

>**Divider (Q):** Supports north, south, east, west and southeast directions. Pops two values off the stack and pushes first/second back. If there is at least no two values on the stack, it does nothing.

>**Modder (%):** Supports northeast and southwest directions. Pops two values off the stack and pushes `std::fmod(first, second)` back. If there is at least no two values on the stack, it does nothing.

### **Constant Adders (I, D)**
Constant adders adds a constant value to the top value of the stack. They inherit from Cable class and return false if `Cable::work()` returns false.

#### **Constant Adder Types**
>**Increaser (I):** Supports north and south directions. Pops the top value off the stack and adds one to it. Then pushes the result back. It does nothing if the stack is empty.

>**Decreaser (D):** Supports east, west, north, south southwest and northwest directions. Pops the top value off the stack and subtracts one from it. Then pushes the result back. It does nothing if the stack is empty.

### **Cloner (#)**
Cloner, clones the value on top of the stack. It inherits from Cable class and return false if `Cable::work()` returns false. It supports north, south, west and east directions. It does nothing if the stack is empty.

### **Constant Pushers (O, @, &)**
Constant pushers push a constant value to the stack. Some of them takes an input from the user and pushes that to the stack. They inherit from Cable class and return false if `Cable::work()` returns false.

#### **Constant Pusher Types**
>**Zero Pusher (O):** Supports all eight directions. Pushes zero to the stack. 

>**Number Pusher (@):** Supports north, south, east, west, northeast, northwest and southwest directions. Takes an input from user as `var_t` and pushes it to the stack.

>**Character Pusher (&):** Supports north, south, east, southeast and southwest directions. Takes an input from user as `char_t` and converts it to `var_t`. Then pushes it to the stack.

### **Swapper ($)**
Swapper, swaps the top two vale on the stack. It inherits from Cable class and return false if `Cable::work()` returns false. It supports north, south, northeast and southwest directions. There must be at least two values on the stack for swapper to work.

### **Conditional Units ([, ])**
Conditional units, kills or spares currents based on the value on top of the stack. They inherit from Cable class and return false if `Cable::work()` returns false. They do nothing if the stack is empty.

#### **Conditional Unit Types**
>**Regular Conditional Unit ([):** Pops the top value off the stack. Kills the current if the top value is zero.

>**Inverted Conditional Unit (]):** Pops the top value off the stack. Kills the current if the top value is not zero.

### **Keys (~, !)**
Keys transform to the other components when they are activated. They will stop current (Technically they move current one step back) if they are not activated. To activate a key, a current must be touch the key from its activator directions. They inherit from Cable class but does not call 'Cable::work()' immidiately.

#### **Key Types**
>**Horizontal Key (~):** Supports east and west directions. Becomes a horizontal cable when activated. Gets activated when a current touches it from north or south directions.

>**Vertical Key (!):** Supports north and south directions. Becomes a vertical cable when activated. Gets activated when a current touches it from east and west directions.

### **Reverser (R)**
Reverser, reverses the entire stack. It inherits from Cable class and return false if `Cable::work()` returns false. It supports north, east, northeast northwest, southwest and southeast directions.

### **Portals**
Every other character in Electra is considered as a portal. Portals support all eight directions. Portals are used for teleporting currents. When Electra reads the source code, it marks first instance of a portal as the original portal. Every other portal connects to the original portal and original portal always connects to portal that the current last used (the portal that teleported current to the original portal). If there is no last used portal, flowing a current on original portal does nothing. I chose this behaviour because It was closest I can get to a function-like behaviour.
