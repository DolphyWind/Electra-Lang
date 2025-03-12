# Electra 2.1
+ [X] Complete rewrite of I/O stuff. (For MSVC support)
+ [X] Update README.md separate implementation details from language spec

# Electra 2.2
+ [X] File I/O
+ [X] Loading components from shared libraries. Like how lua does it

# Future Plans
+ [] Electra standard library
    - A standard library for electra for common tasks.
+ [] Visual Mode: See your code in action!
    - I need to implement [yacw](https://github.com/DolphyWind/yacw) first, because there are no ncurses libraries for my needs. Which is unfortunately not gonna be soon, I have many things to do.
+ [] Electra on the web: Compile and run Electra code in the browser
    - Either compile the code to webassembly or write another interpreter in javascript. Probably the former.
+ [X] Code cleanup

# Cancelled
+ Performance Improvements to brainfuck interpreter
    - I was planning to use two stacks to emulate a tape of a Turing machine, but the current implementation took a weekend to finish. If I find a random motivation, I might do it. But for now it is cancelled.
+ Test gmpxx's floats. Do some benchmarking and if it is suitable, use them to be able to store big numbers.
    - I don't think this is overkill and not needed.
+ Add unit tests
    - The project is quite stable already, and Electra is a toy language. I don't think it is necessary.
