? This is a brainfuck interpreter written electra
? It uses total of seven stacks. So please make sure your stack count is greater than or equal to this value
? This program reads the code from stdin. Please put ! to indicate the end of the code.
? The code gets executed after ! symbol.
? Contains a bug. I have no idea what the bug is but some code straight up don't work

? Stacks are used for these purposes:
? First two stacks are used for storing code.
? Third stack is used for storing index of the current code character
? Forth stack is used for storing loop indices
? Fifth stack holds -1. It is used as a control stack.
? Sixth and seventh stacks are used for memory cells


"util.ec"

? PROGRAM START POINT ?
>-FF--OFF-OD------+
                  |
                  |  ? Push 30,000 zeros to sixth stack ?
                  +--FF-O
                        I
                        I
                        O
                        I
                        I         +-M--}+---------#
                        I         I     n         |
                        I         I     |       +-#-+
                        I         I     |       [   ]
                        +-M###MMM-O     |       B   +-E-+
                                        +---DFO-+       B
                                                        B
                                                        B     +---+
                                                        B     |   |
                                                        B     |   |
                                                        B     U   |
                                     ? Read code here ? +----}+-+ |
                                                                & |
                                                                +-ι
                                                                  E-R
                                                                     *
                                                                     |
                                                                     |
       +-------------------------------------------------------------+
       |
       U
       +-+ +f#O     #-f-B
       n ) |  I     |   |
       | +-+  I     |   +----+
       |      I     |        |
       B      I     I        S
       B      I +-M-+      +-#-+
       |      I I          ]   [
       I      #-+   +------+   |
       E            |          #-F+
       |            +ψ+           I
       B              |           #-b-+
       B              |               S
       B              |             +-#-+
       |              |             ]   [
       +{-------------+     +-------+   |
       n                    |           #-F+
       |                    +ω+            I
       |                      |            #-b-+
       +{---------------------+                S
       n                                     +-#-+
       |                                     ]   [
       |                          +----------+   |
       |                          |              #-F+
       |                          +δ+               I
       |                            |               #-b-+
       +{---------------------------+                   S
       n                                              +-#-+
       |                                              ]   [
       |                               +--------------+   |
       |                               |                  #-F+
       |                               +φ+                   O
       |                                 |                   I      A
       +{--------------------------------+                   I +-M-* *-+
       n                                                     I I       I
       |                                                     #-+       I
       |                                                               #-b-+
       |                                                                   S
       |                                                                 +-#-+
       |                                                                 ]   [
       |                                                          +------+   |
       |                                                          |          #-F+
       |                                                          +λ+           I
       |                                                            |           I
       +{-----------------------------------------------------------+           #-b-+
       n                                                                            S
       |                                                                          +-#-+
       |                                                                          ]   [         A
       |                                                                  +-------+   |    +-M-* *D-#-b-+
       |                                                                  |           #-FO I            S
       |                                                                  +μ+            I #          +-#-+
       |                                                                    |            I I          ]   [
       +{-------------------------------------------------------------------+            I I          |   |
       n                                                                                 +-+     +----+   #-F+
       |                                                                                         |           I
       |                                                                                         +∫F-#       I
       |                                                                                             |       #-b-+
       |                                                                                           +-#-+         S
       |                                                                                           ]   [       +-#-+
       |                                                                                           B   B       [   ]
       |                                                                                           B   B       |   |
       |                    +}+{-------------------------------------------------------------------O   B       |   +-∫F-# 
       |                    | B                                                                        |       |        |
       |                    | $ +---f#F#b-+     +-----#Fb-+      +-------------------------------------+       |      +-#-+
       |                    | I B         S     B         S      $                                             |      ]   [
       |                    | $ B       +-#-+   |         |      #  +--F---------------------------------------+      B   B
       |                    | +-+ +-+   ]   [   I       +-#-+    f  |                                                 B   B
       |                    |     I |   |   |   I       [   ]    B  |                                                 E   B
       |                +--}+{----+ +--FF   F-#-+       |   |    $  |         +------FF-------------------------------+   $
       |                |   n                           |   |    |  |         |                                           |
       |                |   +----------------FF---------+   |    |  |         |                                    +---+  #-F#b-+
       |                |                                   |    |  |         |                                    |   B        $
       |                |       #------------FF-------------+    |  |         |                                    |   |        S
       |                |       |                                |  |         |                                    |   +--f#----+
       |                |     +-#-+                              |  |         |                                    U
       |                |     [   ]                              |  |         |                          +--------}+
       |                |     |   |                              |  |         |                          |         #
       |                |     |   |                              |  |         |                          |         |
       |                |     |   |                              |  |         |                          |       +-#-+
       |                +--D--+   E                              |  |         |                          |       [   ]
       |                          U                              U  |         |                          |       |   |
       +{--------------------FF---+{----------F------------------+{-+         |                          |       B   E
       n                                                                      |                          |       |   |
       |                                                                      |                          +-DFF-b-+   |
       +{---------------------------------------------------------------------+                                      |
       n                                                                                                             |
       +{---------------------------------------------------------------------------------------------------FFF+ +-bF+
                                                                                                               | $
                                                                                                               $ S
                                                                                                               +-+
