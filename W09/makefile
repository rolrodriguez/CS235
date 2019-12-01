###############################################################
# Program:
#     Assignment 09, Binary Search Tree
#     Brother Kirby, CS235
# Author:
#     Jatsiri Detzani & Rolando Rodriguez
# Summary:
#     This assignment implements a Binary Search Tree (BST)
#     using the bynary node from last week as a starting point.
#     A BST is a variation of the binary tree where the parent
#     node is less than or equal to its left child. The right
#     child is greater that the parent and the left child.
# Time:
#	Jatsiri: 25 hours
#       Rolando: 15 hours
#	Team: 02 hours
#
# The most difficult thing:
#	Jatsiri: Erase method was the hardest part for me. I
#               spend most of the time to understand the logic of
#               each case of erase, also I did it by hand to understant it
#               
#	Rolando: For me it was both the insert and the erase
#		methods. I had to do it by hand, one operation after the
#		other one to figure it out, is not that easy by just
#		thinking about how it should be done, as the pointers
#		are tricky and it's easier to make a mistake. 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment09.o
	g++ -o a.out assignment09.o -g
	tar -cf assignment09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment09.o     : the driver program
##############################################################
assignment09.o: bst.h assignment09.cpp
	g++ -c assignment09.cpp -g

