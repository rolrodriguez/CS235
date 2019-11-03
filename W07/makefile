###############################################################
# Program:
#     Assignment 07, LIST
#     Brother Kirby, CS235
# Author:
#     Jatsiri Detzani and Rolando Rodriguez
# Summary:
#     This project includes the a custom::List which is our
#     version of the STL container std::List. With this ADT
#     we solve a problem, calculating Fibonacci number for
#     big numbers, numbers that are not tied to the limits of
#     a regular integer.
#
#	Time:
#		Jatsiri:		XX hours
#		Rolando:		20 hours
#		Pair Programming: 	03 hours
#
#	Challenges:
#		Jatsiri:
#
#		Rolando: This assignment was quite challenging.
#		The insert, erase, copy constructor were
#		difficult for me. I spent a lot of time not
#		getting lost with all there references between
#		nodes. The most difficult thing was the
#		wholenumber class.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h assignment07.o fibonacci.o wholeNumber.o
	g++ -o a.out assignment07.o fibonacci.o wholeNumber.o -g
	tar -cf assignment07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment07.o : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
assignment07.o: list.h assignment07.cpp
	g++ -c assignment07.cpp -g

fibonacci.o: fibonacci.h fibonacci.cpp list.h 
	g++ -c fibonacci.cpp -g

wholeNumber.o: wholeNumber.h wholeNumber.cpp list.h
	g++ -c wholeNumber.cpp -g
