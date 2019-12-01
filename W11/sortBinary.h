/***********************************************************************
 * Module:
 *    Week 11, Sort Binary
 *    Brother Kirby, CS 235
 * Author:
 *    Rolando Rodriguez & Jatsiri Martinez
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include <cassert>
using namespace custom;
using namespace std;
/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
	BST<T> bst; // a new BST is created

	//traverse the unsorted array and insert each element into the BST
	for (int i = 0; i <= num - 1; i++)
		bst.insert(array[i]);

	//with each iteration of the loop, the corresponding tree element
	//is placed back in the array in successive slots.
	//when the BST iterator is complete, all the data will be copied from the BST back into the array.
	int i = 0;
	for (typename BST<T>::iterator it = bst.begin(); it != bst.end(); ++it)
	{
		array[i++] = (*it);
	}
}

#endif // SORT_BINARY_H
