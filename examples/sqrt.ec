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



? The function '√' Calculates the squareroot of the first number on stack ?
? Uses four stacks ?
? First one stores 10 ?
? Second one stores 1e-6 ?
? Third one stores 1 and gets divided by 10 (first cell) time to time ?
? Forth one stores the initial number ?
? Fifth one calculates the squareroot ?
? Then squareroot gets pushed to stack before the first stack ?
? Lastly it clears up all of the stacks it uses ?
? Returns -1 if the number is negative ?
                                                       
                                                       +--------------------------------+
                                                       |                                |
                                                       |                                E
+√-ffff+ +--O                                          |       +E--}+-----+  +-Q-#      |
|      B |  |                                          |       |    n     B  $   |      U
|      B |  I              +QQQQQQ-+                   |       |    |     B  f   B +-FF}+
|      B |  I    A         I       |                   |       g    +L    |  f   # |    |
|      +-+  ###MM *#f######O       |                   |   A   |     |    #  #   f |    |
|                                  FO                  |  * *+-#   +-#    |  B   $ +L   |
|                                   I        ##--+     |  f    |   S |    f  B   S  |   +bbbbb--F×F×F×F×F×+
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

