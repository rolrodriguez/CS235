/***********************************************************************
 * Module:
 *    Week 11, Sort Bubble
 *    Brother Kirby, CS 235
 * Author:
 *    Rolando Rodriguez & Jatsiri Martinez
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/
#include <stdio.h>

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

/*****************************************************
 * SWAP FUNCTION
 * Swap values from two pointers
 ****************************************************/
template <class T>
void swap(T *xp, T *yp) // swap values
{
	T temp = *xp;
	*xp = *yp;
	*yp = temp;
}

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
	bool swapped;

	//iPivot is assigned to the right-most slot
	for (int iPivot = num - 1; iPivot >= 1; iPivot--)
	{
		swapped = false;

		//iCheck moves from the zero index to the pivot for
		//the purpose of bringing the largest element to that slot in the array.
		for (int iCheck = 0; iCheck <= iPivot - 1; iCheck++)
		{
			if (array[iCheck] > array[iCheck + 1]) //if left is greater than right
			{
				swap(&array[iCheck], &array[iCheck + 1]); // swap the values
				swapped = true;
			}
		}
		if (!swapped) //if there are no values to swap, return
			return;
	}
}

#endif // SORT_BUBBLE_H
