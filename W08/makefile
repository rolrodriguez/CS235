###############################################################
# Program:
#     Assignment 08, Binary Tree
#     Brother Kirby, CS235
# Author:
#     Jatsiri & Rolando
# Summary:
#     Implement the binary tree data structure and use it to
#     generate Huffman Codes from a given alphabet
# Coding Time:
#     Jatsiri: 25 hours
#     Rolando: 40 hours
#     Pair time: 3 hours
# The most difficult part:
#   Jatsiri: The insertion operator in BNode.h to display in in LVR order
#      also huffman codes was very difficult for me.. I spent the majority
#      of my time to figure it out and trying to have the logic to generate
#      the code to make it work
#   Rolando: The logic for huffman trees is too complicated still
#      can't think of a way to make it work fully. I understand this is over
#      what we are capable of doing.
#     
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment08.o huffman.o 
	g++ -o a.out assignment08.o huffman.o -g
	tar -cf assignment08.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment08.o : the driver program
#      huffman.o      : the logic for the huffman code program
##############################################################
assignment08.o: bnode.h huffman.h assignment08.cpp
	g++ -c assignment08.cpp -g

huffman.o: bnode.h huffman.h huffman.cpp
	g++ -c huffman.cpp -g

