? Squares a number ?
+²#
| |
+M+

? Clears the current stack ?
+×----+
|     |
|     U
|     +---+
|     n   |
|     | +-+-+
|     E )   (
|     +-+   |
|           |
+-----------+



? The function "√" Calculates the square root of the first number on the stack ?
? Uses five stacks ?
? First one stores 10 ?
? Second one stores 1e-9 ?
? Third one stores 10000 and gets divided by 10 (first cell) when needed ?
? Forth one stores the initial number ?
? Fifth one calculates the squareroot ?
? Then squareroot gets pushed to the stack on the left of the first stack ?
? Lastly it clears up all 5 of the stacks that it uses ?
? Returns -10000 if the number is negative ?
                                                       
                                                       +--------------------------------+
                                                       |                                |
                                                       |                                E
+√-ffff+ +--O       ODDDDDDDDDDODM#M#M+                |       +E--}+-----+  +-Q-#      |
|      B |  |       |                 |                |       |    n     B  $   |      U
|      B |  I       FQQQQQQQQQ+     +-+                |       |    |     B  f   B +-FF}+
|      B |  I    A            I     |                  |       g    +L    |  f   # |    |
|      +-+  ###MM *#f#########O     |                  |   A   |     |    #  #   f |    |
|                                   |                  |  * *+-#   +-#    |  B   $ +L   |
|                                   |        ##--+     |  f    |   S |    f  B   S  |   +bbbbb--F×F×F×F×F×+
+-------------------------------+   FFO+     |   |     |  f    G   $ l    f  |   +--#                     |
                                |      U     | +-+-+   |  f    |   f |    $  B      |                     B
                                |    +}#²B   | [   ]   |  #    |   f B    S  B      l                     B
                                |    |   #   | |   |   |  B    |   f B    +--+      |                     B
                                |    |   f   | |   +---+  B    |   # #              |                     B
                                |    |   S   | |          B    |   B f              #                     B
                                |    |   +---+ +----------#    |   B f              f                     |
                                |    |                         |   B |              f                     |
                                |    |                         +---+ |              |                     |
                                |    |                               A              |                     |
                                |    +----------------------------+{*               |                     |
                                |                                 n                 |                     |
                                |                                 A                 |                     |
                                |                                  *----------------+                     |
                                |                                                                         |
                                +-------------------------------------------------------------------------+



>-@-√N

