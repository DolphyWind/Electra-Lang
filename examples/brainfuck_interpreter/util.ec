? Utility portals (aka functions)
? They expect current from the left of them and they output a current to right when they are done. (Unless specified otherwise)

? Finds the control stack. Always moves right Until it hits a -1 on the top value
+}∫------------+
|              |
|              U
|       +-}+-F}+
|       |  n   |
|       |  | +-+-+
|       |  | (   )
|       |  +-+   #
|       |        I
|       |        |
|       |      +-#-+
|       |      [   ]
|       +------+   |
|                  |
+------------------+

? Decreases the current value. If it is less than zero, it pushes 255 to emulate char behaviour
? If stack is empty it does nothing
+-δ-∫F-+
|      |
|    +-+-+
|    (   )
+{---+   +D--#
n            |
|          +-#-+
|          |   +L
|          l    |
+{---------+    +-E-O
n                   I
|                   I
+-----DMMMMMMM#######

? Increases the current value. If it is greater than 255, it pushes 0 to emulate char behaviour
? If stack is empty it does nothing
+-ψ-∫F-+
|      |
|    +-+-+
|    (   )
+{---+   I
n        #
|        O
|        I
|        I
|        #######MMMMMMMD+
|                       $
|                       S
|                       #
|                     +-+-+
|                     g   G
|                     U   E
+---------------------+{--O


? Checks if the top element on the current stack is equals to '!' character
? It gets input from left. If the top item is equals to '!' it outputs a current to down.
? Otherwise it outputs current to up
+---------------+
U               ]   
ι}-#O           +-+-+
n   I       +-+   # [
|   I       I S   | |
|   ####MMMM+ +---+ |
|                   |
+-------------------+

? Finds the memory stack and moves brainfuck data pointer to right
+}μ-∫Ff-+
|       B
|       +-R
|          *-FbR
|               *
+---------------+

? Finds the memory stack and moves brainfuck data pointer to left
+}λ-∫FR
|      *fB
|        +-R
|           *Fb
|             |
+-------------+

? Prints the byte that is pointed by the data pointer
+-φ-∫-F#P-+
n         |
+---------+

? Reads a byte from stdin and overwrites the byte that is pointed by the data pointer
+-ω-∫-F-E-+
n         &
+---------+






