[![Linux Build](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Linux.yml/badge.svg)](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Linux.yml)  
[![Windows Build](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Windows.yml/badge.svg)](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Windows.yml)  
[![MacOS Build](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Mac.yml/badge.svg)](https://github.com/DolphyWind/Electra-Lang/actions/workflows/Mac.yml)

# What is Electra?

Electra is an [esolang](https://esolangs.org/wiki/Esoteric_programming_language) where you code like an electrician. Electra is inspired by [AsciiDots](https://esolangs.org/wiki/AsciiDots). It uses instruction pointers that act like currents in electricity. [Here's](https://esolangs.org/wiki/Electra) the esolang wiki page if you are interested.  

# How to get Electra?

If you are on Arch Linux or a Linux distribution that is based on Arch Linux, you can download Electra using the [AUR](https://aur.archlinux.org). To download Electra from AUR, install an AUR helper like `yay`. Then type the command below into the terminal to install Electra.

```bash
yay -S electra-git
```  
If you are on a Linux distribution that is not Arch Linux based, or using completely different operating system. Currently, the only option to get Electra running on your system is building Electra from source. To build Electra from source, open up a terminal and follow the steps below.

## Building on Unix-Like Operating Systems

If you are on a Unix-Like operating system such as Linux, MacOS, BSD etc. To build Electra from source, first, install git, CMake and make tools using your package manager. Then type these commands in a terminal

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

If you are on Windows, please install [Git for Windows](https://gitforwindows.org/), and [CMake](https://cmake.org/download/) alongside a C++ compiler and add them to your PATH. MSVC is now supported. To build Electra on Windows, follow the steps below.

```bash
# Clone the repository and cd into it
git clone https://github.com/DolphyWind/Electra-Lang.git
cd Electra-Lang
# Create a build directory
mkdir build
cd build
# Run cmake to generate build files
cmake ..
# Build Electra 
cmake --build . --config="Release"
```

# How Electra works?
Electra has Currents, Generators and Components. Electra uses a list of 64 stacks of double-precision floating-point numbers for its memory.
(This implementation has a command line argument that allow you to change the stack count)

## **Comments, Including Other Files and Extending Electra With C++**
In Electra, you can comment out your code using question marks. 
```
? This is a comment ? >-+ 
                        & ? This is also a comment. It lasts a whole line
                         *P
```

To include other files in your code, use quotation marks.
```
? Copies the contents of file.ec and pastes it all into the current file ?
"file.ec"

? Electra will prevent you from reincluding a file. This will do nothing ?
"file.ec"

? Putting '!' before filename forces Electra to reinclude given file ?
"!file.ec" 

? You can also specify a range when including a file ?
? (x < y) ?
"mylib.ec" x:y ? Includes the lines between the line x and the line y (x-inclusive, y-exclusive) ?
"otherlib.ec" x: ? Includes the lines after the line x (x-inclusive) ?
"anotherlib.ec" :y ? Includes the lines before the line y (y-exclusive) ?

? Electra prevents you to reincluding a portion that has already been included before ?
"foo.ec" 10:15
"foo.ec" 5:12 ? This will do nothing ?
"!foo.ec" 5:12 ? You can always do a force include ?
```

But be careful, files ending with `.dll`, `.so` or `.dylib` will be treated as packages.
This behavior depends on your platform, for example, on Windows only the `.dll` files will be treated as packages, on Linux, it is `.so` files
and on Mac it is the `.dylib` files.
Packages allow you to extend Electra using C++. For more info, click [here](ExtendingElectra.md).

## **Currents**
Currents are instruction pointers in Electra. They all have a direction, a position, a stack that holds visited portals and a stack pointer.
A direction can take one of these eight values: East, Northeast, North, Northwest, West, Southwest, South, Southeast.
On each iteration of Electra's main loop, each current moves one step forward.
When a current touches a component, if the component supports a current coming from that direction,
component does its work and uses that current's stack pointer when doing stack manipulations. And after it has done its work, it either kills or clones that current.
A current can either be generated by a generator, or be cloned by other components.

## **Generators**
Generators generate currents at the beginning of an Electra program and become useless immediately.
They generate current based on the direction that they are facing. To make looping easier, generators also let currents flowing on them.
They support the direction in which they generate current and its opposite. (e.g. an east generator supports both east and west directions)

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
Components are the elements that give Electra its functionality.
Each component has its own job and can clone or kill existing currents (Except for Portals, they teleport currents).  
If a current flows into a component from an unsupported direction, that current gets killed.
But components can also kill a current after they've done their work.
If a current lives and the component supports directions that are different from the current's direction or its opposite, it gets cloned.
This will be explained better in the following section.

### **Cables**
Cables are used to transmit currents in Electra. Some cables also clone currents.

For example:

    >-----+-
          |

The regular four directional cable (+) has a current flowing from west and heading to east. It will create 2 more copies of that current with directions north and south.
The current with direction north will die in the next iteration.

#### **Cable Types**
>**Horizontal Cable (-):** Supports east and west directions. Simple cable for flowing current horizontally.

>**Vertical Cable (|):** Supports north and south directions. Simple cable for flowing current vertically.

>**Right Diagonal Cable (/, ╱):** Supports northeast and southwest directions. Simple cable for flowing current diagonally.

>**Left Diagonal Cable (\\, ╲):** Supports northwest and southeast directions. Simple cable for flowing current diagonally.

>**Regular Four Directional Cable (+, ┼):** Supports east, west, north and south directions. Can be used to change direction of a current or clone it.

>**Diagonal Four Directional Cable (X, ╳):** Supports northeast, northwest, southeast and southwest directions. Can be used to change direction of a current or clone it.

>**Eight Directional Cable (\*, ✱):** Supports all directions. Can be used to change direction of a current or clone it.

>**East One Directional Cable (}):** Only lets a current flowing to east direction to pass.

>**West One Directional Cable ({):** Only lets a current flowing to west direction to pass.

>**North One Directional Cable (n):** Only lets a current flowing to north direction to pass.

>**South One Directional Cable (U):** Only lets a current flowing to south direction to pass.

>**Other Cables (╰, └, ╯, ┘, ╭, ┌, ┐, ╮, ├ ,┤ ,┬ ,┴):** These cables are not special they just have no name. They flow current based on how they look like.

### **Printers**
Printers print the value on top of the stack. They can print a variable either as a number or as a character.

#### **Printer Types**
>**Number Printer (N):** Supports east, northeast, northwest, west, southwest and southeast directions. Pops the top value off the stack and prints it as number. If the stack is empty it does nothing.

>**Character Printer (P):** Supports east, northeast, north, northwest, west, and southwest directions. Pops the top value off the stack, converts that number to a UTF-8 code point and prints it. If the stack is empty it does nothing.

### **Arithmetical Units**
Arithmetical units let Electra do arithmetical calculations. If there are less than two values on the stack, they do nothing.

#### **Arithmetical Unit Types**
>**Adder (A):** Supports north, southwest and southeast directions. Pops two values off the stack and pushes `first+second` back. 

>**Subtracter (S):** Supports northeast, north, southwest and south directions. Pops two values off the stack and pushes `first-second` back. 

>**Multiplier (M):** Supports east, northeast, northwest, west, southwest, south and southeast directions. Pops two values off the stack and pushes `first*second` back. 

>**Divider (Q):** Supports east, north, west, south and southeast directions. Pops two values off the stack and pushes `first/second` back. 

>**Modder (%):** Supports northeast and southwest directions. Pops two values off the stack and pushes `first%second` back where `%` is the fmod operation. 

### **Constant Adders (I, D)**
Constant adders add a constant value to the value that is on top of the stack. 

#### **Constant Adder Types**
>**Increaser (I):** Supports north and south directions. Pops the top value off the stack and adds one to it. Then pushes the result back. It does nothing if the stack is empty.

>**Decreaser (D):** Supports east, north, northwest, west, southwest and south directions. Pops the top value off the stack and subtracts one from it. Then pushes the result back. It does nothing if the stack is empty.

### **Cloner (#)**
Cloner, clones the value on top of the stack. It supports east, north, west and south directions. It does nothing if the stack is empty.

### **Constant Pusher (O)**
Constant pusher, pushes a constant value to the stack. There is currently only one constant pusher and it pushes 0 to the stack. Supports all eight directions.

### **Readers**
Readers, read user's input.

#### **Reader Types** 
>**Number Reader (@):** Supports east, northeast, north, northwest, west, southwest and south directions. Takes an input from user as a number and pushes it onto the stack.

>**Character Reader (&):** Supports north, south, east, southeast and southwest directions. Takes a single UTF-8 code point from user as input, then converts it to its corresponding number value and pushes it onto the stack.

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
Stack switchers move the current's stack pointer forwards or backwards. Some of them pops the top value and moves it to the next stack. Stack switchers do wrap around if a stack pointer ends up exceeding the limits. 
They stack pointer wraps around if you try to move it out of bounds.

>**Forward Stack Switcher (F):** Supports east, northeast, north, northwest, west and southwest directions. Moves current's stack pointer forward. Does not move top value to the next stack.

>**Forward Moving Stack Switcher (f):** Supports east, northeast, north, west and south directions. Moves current's stack pointer forward. Does move top value to the next stack if stack is not empty.

>**Backward Stack Switcher (B):** Supports northeast, north, northwest, west, southwest, south and southeast directions. Moves current's stack pointer backward. Does not move top value to the next stack.

>**Backward Moving Stack Switcher (b):** Supports east, northwest, west, southwest, south and southeast directions. Moves current's stack pointer backward. Does move top value to the next stack if stack is not empty.

### **Keys**
Keys transform to the other components when they are activated. They will keep the current still until they are activated. To activate a key, a current must be touch the key from its activator directions. 

#### **Key Types**
>**Horizontal Key (~):** Supports east and west directions. Becomes a horizontal cable when activated. Gets activated when a current touches it from north or south directions.

>**Vertical Key (!):** Supports north and south directions. Becomes a vertical cable when activated. Gets activated when a current touches it from east and west directions.

### **Reverser (R)**
Supports north, east, northeast northwest, southwest and southeast directions. Reverser, reverses the entire stack.

### **Eraser (E)**
Supports all eight directions. Eraser, pops off the top value from the stack. 

### **Bomb (o)**
Supports all eight directions. Finishes the program execution.

### **File Reader (r)**
Supports northeast, north, northwest, west and southwest directions. Continuously pops the value on top of the stack and constructs a filename from those values until either it hits a zero or the stack becomes empty. (If it hits a zero, it also pops that)  
Then, it reads the file with that filename in binary mode, pushes its content on top of the stack in reverse order and the length of the string. If it fails to open the file, it only pushes a zero to the stack.

### **File Openers**
Similar to File Reader, File Openers read a filename from the stack in the same way. After opening the file, they push a positive integer as unique identifier that can be used to communicate with file.
They push zero on failure.

>**File Write Opener(w):** Supports east, west, southwest and southeast directions. Opens the file in write and binary modes and pushes its id to the stack.

>**File Append Opener(a):** Supports east, northeast, north, northwest, west, southwest, south and southeast directions. Opens the file in append and binary modes and pushes its id to the stack.

### **File Writer (W)**
File writer first pops the value on top of the stack and uses it as a file id. Then, constructs a string just like how the File Reader constructs a filename.
Then writes that string to the file. It pushes zero on failure.

### **File Closer (C)**
File closer pops the value on top of the stack and closes that file handler. It pushes zero on failure.

### **Portals**
Every other character in Electra is a portal. Portals support all eight directions.
They are used for teleporting currents. When Electra reads the source code, it marks the first instance of a portal as the original portal.
When you flow a current to an unoriginal portal, the portal gets pushed to that current's visited portals stack, and the current gets teleported
to the original portal. Flowing a current to the original portal teleports the current back to the last visited portal and pops it off the stack.
If the stack is empty, flowing a current to the original portal does nothing. They are somewhat analogous to functions in other programming languages.

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

# About This Implementation
This interpreter has implemented Electra by using OOP and inheritance. There is a class named Component.
Every component has a `work()` function and currents call the work function of the components that they are sitting on.
The Cable class inherits from Component class and clones the currents in its `work()` function.
Every other component inherits from Cable class except for Portal, it directly inherits from Component.

The interpreter has these command line arguments:
- `--help` or `-h`: Prints a help message and exits.
- `--version` or `-v`: Prints the version and exits.
- `--log` or `-l`: Enables logging. Electra interpreter logs each step of the program and saves it into a file.
- `--stack <arg>` or `-s <arg>`: Specifies some initial values for stacks. For example, `-s "0 1 2,3 4 5"` Pushes 0,1 and 2 to the first stack and 3, 4 and 5 to the second stack.
- `--stack-count <arg>` or `-sc <arg>`: Sets the stack count. The default stack count is 64.
