###############################################################
# Program:
#    Assignment 11, Sorts
#    Brother Kirby, CS235
# Author:
#    Rolando Rodriguez & Jatsiri Martinez
# Summary:
#    Implement several sorting algorithms: the bubble sort,
#    selection sort, insertion sort, binary sort, heap sort,
#    merge sort and quick sort.
# Coding Time:
#    Pair programming: 1 hour
#    Rolando: 24 hours
#    Jatsiri: 30 hours
#
# The most difficult part:
#    Rolando: The most difficult was the merge sort, we  
#    had to start from scratch several times, and review to
#    make it work.
#
#    Jatsiri: The most difficult part for me was the merge sort.
#    I wrote a lot of times the code, to test different ways
#    but it was difficult for me to make it work correctly 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment11.o
	g++ -o a.out assignment11.o -g
	tar -cf assignment11.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment11.o     : the driver program
##############################################################
assignment11.o: assignment11.cpp sortValue.h \
		sortBinary.h sortInsertion.h sortHeap.h sortBubble.h \
		sortSelection.h sortMerge.h sortQuick.h
	g++ -c assignment11.cpp -g

