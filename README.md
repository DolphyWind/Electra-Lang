[![Linux Build](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Linux.yml/badge.svg)](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Linux.yml)  
[![Windows Build](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Windows.yml/badge.svg)](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Windows.yml)  
[![MacOS Build](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Mac.yml/badge.svg)](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Mac.yml)

# What is Electra?

Electra is an [esolang](https://esolangs.org/wiki/Esoteric_programming_language) where you code like an electrician. Electra is inspired by [AsciiDots](https://esolangs.org/wiki/AsciiDots). It uses instruction pointers that acts like currents in electricity. [Here's](https://esolangs.org/wiki/Electra) the esolang wiki page if you are interested.  

# How to get electra?

If you are on Arch Linux or a Linux distrubution that is based on Arch Linux, you can download Electra using the [AUR](https://aur.archlinux.org). To download electra from AUR, install an AUR helper like `yay`. Then type the command below into the terminal to install Electra.

```bash
yay -S electra-git
```  
If you are on a Linux distrubution that is not Arch Linux based, or using completely different operating system. Currently the only option to get Electra running on your system is building Electra from source. To build Electra from source, open up a terminal and follow the steps below.

## Building on Unix-Like Operating Systems

If you are on a Unix-Like operating system such as Linux, MacOS, BSD etc. To build electra from source, first, install git, cmake and make using your package manager. Then type these commands in a terminal

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

If you are on Windows, please install [Git for Windows](https://gitforwindows.org/), [Mingw-w64](https://www.mingw-w64.org/downloads/), [CMake](https://cmake.org/download/) and add them to your PATH. Building with Visual Studio is currently NOT supported. Also, please note that Windows build is a bit unstable and might not work in your system. It worked on my Windows 10 and Windows 11 machines but for some reason it doesn't work on my virtual machines. To build electra on windows, follow the steps below.

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

Electra has Currents, Generators and Components. Currents are instruction pointers that acts like the currents in electricity, Generators generate currents and Components interpret currents to make code function. Electra uses list of stacks of doubles for memory management. The total stack count is 64 by default but can be manuplated with `--stack-count` argument of the Electra interpreter. Every current has its own stack pointer. That way doing some maniplations to different stacks at the same time is possible. Electra also supports commenting your code in line and including other files. To comment a portion of your code, use question marks `? like this ?` (The last one is not required if you want a comment lasting a whole line). To include other files in your code, use double quotes: `"file.ec" x:y`. This will include the lines in range from x to y (x-inclusive, y-exclusive). If you don't specify any lines electra will include whole file into your code. By default, reincluding a part is disabled. If you want to reinclude a part, add `!` before filename: `"!file.ec" x:y`. But remember to use this with caution.

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

>**Southwest Generator (↙):** Generates a current with southwest direction.

>**Southeast Generator (↘):** Generates a current with southeast direction.

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

>**Other Cables (╰, └, ╯, ┘, ╭, ┌, ┐, ╮, ├ ,┤ ,┬ ,┴):** These cables are not special they just have no name. They flow current based on how they look like.

### **Printers**
Printers print out the variables on the stack. They can print a variable either as a number or as a character.

#### **Printer Types**
>**Number Printer (N):** Supports east, northeast, northwest, west, southwest and southeast directions. Pops the top value off the stack and prints it as number. If the stack is empty it does nothing.

>**Character Printer (P):** Supports east, northeast, north, northwest, west, and southwest directions. Pops the top value off the stack and prints it as a character. If the stack is empty it does nothing.

### **Arithmetical Units**
Arithmetical units lets Electra do arithmetical calculations. If there is less than two values on the stack they do nothing.

#### **Arithmetical Unit Types**
>**Adder (A):** Supports north, southwest and southeast directions. Pops two values off the stack and pushes first+second back. 

>**Subtracter (S):** Supports northeast, north, southwest and south directions. Pops two values off the stack and pushes first-second back. 

>**Multiplier (M):** Supports east, northeast, northwest, west, southwest, south and southeast directions. Pops two values off the stack and pushes first*second back. 

>**Divider (Q):** Supports east, north, west, south and southeast directions. Pops two values off the stack and pushes first/second back. 

>**Modder (%):** Supports northeast and southwest directions. Pops two values off the stack and pushes `std::fmod(first, second)` back. 

### **Constant Adders (I, D)**
Constant adders adds a constant value to the top value of the stack. 

#### **Constant Adder Types**
>**Increaser (I):** Supports north and south directions. Pops the top value off the stack and adds one to it. Then pushes the result back. It does nothing if the stack is empty.

>**Decreaser (D):** Supports east, north, northwest, west, southwest and south directions. Pops the top value off the stack and subtracts one from it. Then pushes the result back. It does nothing if the stack is empty.

### **Cloner (#)**
Cloner, clones the value on top of the stack. It supports east, north, west and south directions. It does nothing if the stack is empty.

### **Constant Pusher (O)**
Constant pusher, pushes a constant value to the stack. There is currently only one constant pusher and it pushes 0 to the stack. Supports all eight directions.

### **Readers**
Readers are components that can read user's input.

#### **Reader Types** 
>**Number Reader (@):** Supports east, northeast, north, northwest, west, southwest and south directions. Takes an input from user as number and pushes it to the stack.

>**Character Reader (&):** Supports north, south, east, southeast and southwest directions. Takes an input from user as chaacter and converts it to number. Then pushes it to the stack.

### **Swapper ($)**
Swapper, swaps the top two values on the stack. It supports north, south, northeast and southwest directions. There must be at least two values on the stack for swapper to work.

### **Conditional Units**
Conditional units, kill the current or let it flow based on the value on top of the stack. They do nothing if the stack is empty.

#### **Conditional Unit Types**
>**Equals Conditional Unit (]):** Supports north and south directions. Pops the top value off the stack. Lets the current flow if the top value is equals zero.

>**Not Equals Conditional Unit ([):** Supports north and south directions. Pops the top value off the stack. Lets the current flow if the top value is not equals zero.

>**Greater Than Conditional Unit (G):** Supports east, north, northwest, west, southwest, south and southeast directions. Pops the top value off the stack. Lets the current flow if the top value is greater than zero.

>**Not Greater Than Conditional Unit (g):** Supports northeast, north, northwest, southwest, south and southeast directions. Pops the top value off the stack. Lets the current flow if the top value is not greater than zero.

>**Less Than Conditional Unit (L):** Supports northwest, west, southwest, south and southeast directions. Pops the top value off the stack. Lets the current flow if the top value is less than zero.

>**Not Less Than Conditional Unit (l):** Supports north and south directions. Pops the top value off the stack. Lets the current flow if the top value is not less than zero.

### **Stack Checkers**
Stack checkers, check whether the current stack is empty or not. 

>**Regular Stack Checker( ( ):** Supports north and south directions. Lets the current flow if the stack is empty.

>**Inverted Stack Checker( ) ):** Supports north and south directions. Lets the current flow if the stack is not empty.

### **Stack Switchers**
Stack switchers move the current's stack pointer forwards or backwards. Some of them pops the top value and moves it to next stack.

>**Forward Stack Switcher (F):** Supports east, northeast, north, northwest, west and southwest directions. Moves current's stack pointer forward. Does not move top value to the next stack.

>**Forward Moving Stack Switcher (f):** Supports east, northeast, north, west and south directions. Moves current's stack pointer forward. Does move top value to the next stack if stack is not empty.

>**Backward Stack Switcher (B):** Supports northeast, north, northwest, west, southwest, south and southeast directions. Moves current's stack pointer backward. Does not move top value to the next stack.

>**Backward Moving Stack Switcher (b):** Supports east, northwest, west, southwest, south and southeast directions. Moves current's stack pointer backward. Does move top value to the next stack if stack is not empty.

### **Keys**
Keys transform to the other components when they are activated. They will stop current (Technically they move current one step back) if they are not activated. To activate a key, a current must be touch the key from its activator directions. 

#### **Key Types**
>**Horizontal Key (~):** Supports east and west directions. Becomes a horizontal cable when activated. Gets activated when a current touches it from north or south directions.

>**Vertical Key (!):** Supports north and south directions. Becomes a vertical cable when activated. Gets activated when a current touches it from east and west directions.

### **Reverser (R)**
Supports north, east, northeast northwest, southwest and southeast directions. Reverser, reverses the entire stack.

### **Eraser (E)**
Supports all eight directions. Eraser, erases the top value from the stack. 

### **Bomb (o)**
Supports all eight directions. Finishes the program execution.

### **Portals**
Every other character in Electra is considered as a portal. Portals support all eight directions. They are used for teleporting currents. When Electra reads the source code, it marks first instance of a portal as the original portal. Every other portal connects to the original portal and original portal always connects back to the portal that teleported current to the original portal. If there is no last used portal, flowing a current on original portal does nothing. Think of them as the functions in Electra.

# Examples 
Here are some example programs written in Electra:

### **Hello World!**
A program that prints the phrase "Hello World!" to the terminal screen.
```
    >O    +-+     +-+     +-+                                     Q-PO
     I    I I   #P+ I     I I                                     $  I
     I +MPO I   I   I     O I                                     I  I +P
     I I    I #M+   I     | $                                     I  I I
     I I    I I     I   #P# QDDDDD#P+DDDO                         I  #M+
     I O    I I     I   I               I    #PDDDDDD#PDDDDDDDD#PDO    
     I |    I I     I   I               I    I
     #M+    +-+     I   I               I    I
                    ##PP+               $    I
                                        +MP#P+
```

### **truth-machine**
truth-machine, takes an input from user; halts if the input is zero, prints one indefinitely if the input is one. truth-machine is used to test any esolang (or any other programming languages) whether if it is capable of doing this four basic operations:
1. Input
2. Output
3. Looping
4. Termination
```
    >@
    
    +->--#N+
    |      |
    |      #
    |      [
    +------+
```

### **FizzBuzz** 
A FizzBuzz program, starts to loop from 1 to N. For each number; prints "Fizz" if the number is divisible by 3, prints "Buzz" if the number is divisible by 5, prints "FizzBuzz" if the number is both divisible by 3 and 5. Prints the number if the number is not divisible by either 3 or 5.

```
    +-0-O         +-1-O         +-2-O     +-+  
    |   I         |   I         |   I     D D  
    |   I         |   I         |   I     D D  
    |   I         |   I         |   I     D D  
    |   I         P   I         |   I     D D     +---+
    |   I        *    I         |   I     D D     I   I
    |   I        |    I         |   I  #P-# D     I   #M+
    |   I        A    I         |   I  I    D   +5O     I
    |   I         *   I DM#--P  |   I  I    D   |       |
    |   I         Q   I D   /   |   #M-+    D   +-----P-+
    |   I #PP+    $   I D  *    |           D  
    |   I I  |    I   #-+  #    |           A  
    |   #M+  |    I        O    +------P---*   
    |        |    +--------+    
    +--------+ 
    
    +3-1-0-+ +4-2-0-+
    |      | |      |
    +------+ +------+
    
    >---O
        I
        I      ####MMMMP+
        I      I        |
        I      I        |
        |      O        |
        |      |        |
        ##MMDDP+        |
                        |
        +---------------+
        @
        I
        #
        #
        O
    +>--~--+
    |      I
    |      $
    |      S
    |      ##-----+--+
    |             [  ]
    |             |  
    |             |
    |             |
    |             |
    |             |
    |             $
    |             S
    |             $
    |             #
    |             #
    |            #R
    |            |
    |            O
    |            I
    |            I
    |            I *-#-+
    |            $%  [ ]
    |            *   | +-3+
    |              +-+    |
    |              |      |
    |          +-O-#      |
    |          I          |
    |          I          |
    |          I          |
    |          I          |
    |          I *-#-+    |
    |          $%  [ ]    |
    |          *   | |    |
    |              | |    |
    |            +N# |    |
    |            U   |    |
    |            +{--+    |
    |            |        |
    |            +----+   |
    |                 U   |
    |             +-O-#{--+
    |             I
    |             I
    |             I
    |             I
    |             I *-#-+
    |             $%  [ ]
    |             *   | +-4+
    |                 |    |
    |                 U    |
    |               +-+{---+
    |               |
    |               +-5+
    |                  |
    +------------------+
```
