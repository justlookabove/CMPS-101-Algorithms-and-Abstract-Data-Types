Kiran Gunasekaran
CMPS 101


List.c - Abstract data type implemented as a doubly linked list
	that contains the Node class, constructors, access functions,
	manipulation functions, and other functions that defines the
	List object

Lex.c - Main client for the List ADT, takes two file names as parameters,
	the first being the input file and the second being the output
	file. Using a variation of Insertion Sort, the client can
	alphabetize the input text file using the indexes determined by
	its original line number and building a List object that sorts
	the input array of words. The List is then used to print the array
	to the output file in alphabetical order
List.h - Header file containing all the function variables for initialization 
	 for the List.c file.

Makefile - File used to compile the source code and create executable 
	      jar Lex file. Provided by Professor.


ListClient.c - Program provided by professor to test the List ADT

Use cc --std=c99 while compiling.