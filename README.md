# LFA_Homework3

## Task1: Implement Cyk's Algorithm *(cyk_algorithm.cpp)*
Input format *(test.in)*:\
*example:*\
4 -> 4 non-terminal symbols\
S -> symbol nr1\
2 -> number of production rules for symbol nr1\
0 AB\
0 BC\
A -> symbol nr2\
2 -> number of production rules for symbol nr2\
0 BA\
1 a\
B -> symbol nr3\
2 -> number of production rules for symbol nr3\
0 CC\
1 b\
C -> symbol nr4\
2 -> number of production rules for symbol nr4\
0 AB\
1 a
stdin: message that needs to be verified

This source outputs both in the user console and the *test.out* file. It also outputs the CFG in a nice format.

## Task2: Implement a pushdown automata *(pushdown_automata.cpp)*
*("Choose between deterministic PDA and non-deterministic PDA" -> I chose to implement non-deterministic)*
Input format *(test.in)*:\
*example*:*\
4 -> number of states\
0 1 2 3 -> the states\
0 -> the source\
1 -> number of terminal states\
3 -> list of terminal states (all on the same line)\
5 -> number of transitions (X, Y, accepted_char, popped_char, pushed_char) where the edge is directed from X to Y)\
0 1 ^ ^ $\
1 1 0 ^ 0\
1 2 ^ ^ ^\
2 2 1 0 ^\
2 3 ^ $ ^\
000111 -> the message to be verified

*Observation* : This input defines a pushdown automata that accepts {0^n 1^n : n >= 0)

This source outputs both in the user console and the *test.out* file. It also outputs the automata in a nice format.
