###############################################################
# Program:
#     Assignment 02, STACK
#     Brother Kirby, CS235
# Author:
#     Jatsiri Detzani and Rolando Rodriguez
# Summary:
#     This makefile includes an implementation of
#			a stack container, similar to the STL implementation
#			of std::stack. In this assignment we solved a
#			problem with the stack container: to convert
#			from infix notation to postfix notation. We pushed
#			a bit more to implement as well the conversion from
#			postfix to assembly notation.
# Time:
#     It took us about 20 hours to finish everything.
#			pair programming sessions on wednesday, thursday,
#			friday and the assembly assignment on saturday.
#
#			Jatziri's time:		20 hrs
#			Rolando's time: 	20 hrs
#			Discussion time:	07 hrs
#
# Difficulties:
#			The most difficult part of this assignment was 
#			Tokenizing the input, following through with the
#			program flow by paper and pencil to make sure the 
#			logic worked.	
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h assignment02.o infix.o 
	g++ -o a.out assignment02.o infix.o 
	tar -cf assignment02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment02.o : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
assignment02.o: stack.h infix.h assignment02.cpp
	g++ -c assignment02.cpp  

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp 

