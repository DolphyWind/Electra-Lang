# Electra 2.0

+ Add a component that checks if the current stack is empty or not called stack checker. Use these characters: ().
+ Add a way to comment the code. Something like ? This is a comment ?
+ Add a way to include other code files. Something like ?? filename.ec x:y. Includes the lines in range [x, y)in filename.ec.
+ Increase the stack size and add stack switcher component(s).  
I might increase the total stack count to 16 and add two components for switching the stacks.  
Also an argument called --stack-count for managing stack count would be great.
+ Update --stack's formatting to something like this: "1 2 3,4 5 6". First stack contains 321, second stack contains 654
+ Add unicode versions of cables and other components.
+ Make ConstantPusher and Input components seperated. Input components will be called Reader. This won't change how language works. It just makes more sense to keep them seperated.
+ Comment out the code in general
+ Greatly modify README.md
    + Explain how Electra 2.0 works including multiple stacks and each current having its own stackPtr
