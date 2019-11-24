###############################################################
# Program:
#     Assignment 10, Map
#     Brother Kirby, CS 235
# Author:
#     Rolando & Jatsiri
# Summary:
#     Implement the map data structure and use it to count the
#     frequency of words in a large file.
# Coding Time:
#     Pair programing:
#     Rolando: 38 hours
#     Jatsiri: 40 hours
#			Pair Programming: 3 hours
#
# The most difficult part:
#     Rolando: The most difficult part for me was the iterator for
#			the map class. We spent hours trying to solve the segmentation faults.
#			Also to make sense of how a pointer class relates to the iterator of
#			other can become a nightmare quite fast.
#
#     Jatsiri: The hardest part for me was working in the map
#         iterator, to pass the test 3. Working with the pointers
#         in this assignment confused me a lot. Also in count words
#         the part of displaying the words correctly and store the
#         words in the file.
#
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment10.o wordCount.o
	g++ -o a.out assignment10.o wordCount.o -g
	tar -cf assignment10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment10.o : the driver program
#      wordCount.o    : the wordCount() function
##############################################################
assignment10.o: pair.h map.h bst.h assignment10.cpp
	g++ -c assignment10.cpp -g

wordCount.o: map.h bst.h wordCount.h wordCount.cpp 
	g++ -c wordCount.cpp -g
