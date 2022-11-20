###############################################################
# Program:
#     Assignment 06, NODE
#     Brother Kirby, CS235
# Authors:
#     Rolando Rodriguez and Jatsiri Martinez
# Summary:
#     Implement a linked-list and use it to inplement Insertion Sort.
# Coding Time:
#     Pair programing: 2 hour
#     Jatsiri: 15 hours
#     Rolando: 7 hours
# The most difficult part:
#     Jatsiri: The most difficult part was to understand the logic of
#        insertion() function to insert the new node after the current node
#        and operator << to display correctly the elements.
#     Rolando: The most difficult part was to make sense of the
#	pointers and the insert function. The insertion sort
#	was not that complicated, we had the temptation of
#	looking at other algorithms.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: node.h assignment06.o 
	g++ -o a.out assignment06.o -g
	tar -cf assignment06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment06.o      : the driver program
#      <anything else?>
##############################################################
assignment06.o: node.h assignment06.cpp sortInsertion.h
	g++ -c assignment06.cpp -g 
