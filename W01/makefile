###############################################################
# Program:
#     Assignment 01, Vector
#     Brother Kirby, CS235
# Author:
#     Rolando Rodriguez
# Summary:
#     This program includes the vector.h file which is an
#			implementation of the STL vector container. This 
#			container resizes as needed to hold the elements.
# Time:
#     It took me about 6 hours to do it. It's been a while
#			since I took other C++ classes.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: vector.h assignment01.o
	g++ -o a.out assignment01.o
	tar -cf assignment01.tar vector.h assignment01.cpp makefile

##############################################################
# The individual components
#      assignment01.o     : the driver program
##############################################################
assignment01.o: vector.h assignment01.cpp
	g++ -c assignment01.cpp

