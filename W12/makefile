###############################################################
# Program:
#     Assignment 12, Hash
#     Brother Kirby, CS235
# Authors:
#     Rolando Rodriguez & Jatsiri Martínez
# Summary:
#     Implement the hash data sructure and use it to implement a
#     spell checker.
#
# Coding Time:
#   Pair Preogramming: 1 hour
#   Rolando: 10 hours
#   Jatsiri: 25 hours
#
# The most difficult part:
#   Rolando: My highest difficulty was related to populating the
#   dictionary to memory and comparing which words were misspelled.
#   A function to make words to lowercase was made.
#
#   Jatsiri: The hardest part was compare and check the words and then
#   display the list of te misspelled words. Also the logic of
#   the hash function.
#
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment12.o spellCheck.o
	g++ -o a.out assignment12.o spellCheck.o -g 
	tar -cf assignment12.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment12.o     : the driver program
#      spellCheck.o       : the spell-check program and driver
##############################################################
assignment12.o: hash.h assignment12.cpp list.h
	g++ -c assignment12.cpp

spellCheck.o: hash.h spellCheck.h spellCheck.cpp
	g++ -c spellCheck.cpp -g

