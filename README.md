Practicing for the OMP'19
===================================

I will upload here the solutions to the problems with which I practice.

OMP'18-E (Finite Automaton)
===================================
Bididibus consists of blocks of uniform width and height. Bididibusian orography is described by a series of symbols, from left to right, indicating that the land rises one unit (represented by "/"), descends one unit (represented by "\"), or it is flat (represented by "_").
Your task is to count the number of plateaus in the map. A valid plateau should have: 3 or more consecutive rising units; 1 or more flat units; and 3 or more consecutive descending units.

OMP'18-G (Backtracking)
===================================
To know all the possible results of a program assuming sequential consistency, all possible interleavings of the instructions in different threads have to be tested.
Assuming that all variables are initialized to 0.
Your task is to write a program that given a printed sequence, tells you if the program was executed following sequential consistency, that is, respecting the order of the instructions in the thread.
The program input begins with a number indicating the number of programs. The programs follow in the next lines. A program has always two threads. Each thread has a number of instructions less than 10, and each instruction goes in a different line. Each instruction can be of the type "variable = value" or of the type "print variable". Variables are represented by single character (from 'a' to 'z') and values are a single digit (from '0' to '9'). The code of each thread finishes with the character hash ('#'). After the code, each line represents a possible result. The list of results ends with the character hash ('#').
