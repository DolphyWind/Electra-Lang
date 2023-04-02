# Electra 2.0

+ Add a component that instantly ends the program called bomb.
+ Add a component that checks if the current stack is empty or not called stack checker.
+ Add a way to comment the code. Something like ? This is a comment ?
+ Add a way to include other code files. Something like ?? filename.ec x:y. Includes the lines in range [x, y)in filename.ec.
+ Increase the stack size and add stack switcher component(s).  
I might increase the total stack count to 16 and add two components for switching the stacks.  
Also an argument called --stack-count for managing stack count would be great.
+ Update --stack's formatting to something like this: "1 2 3,4 5 6". First stack contains 321, second stack contains 654
+ Add support for unicode characters. This might break the windows compatability though, because my every attempt of reading unicode from file with MSVC failed. But I got it worked on MinGW.
+ Add unicode versions of cables and other components.
+ Make each current have their own stack pointer this way multithreading would be a safe option.
