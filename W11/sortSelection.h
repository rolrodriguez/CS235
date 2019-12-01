/***********************************************************************
 * Module:
 *    Week 11, Sort Select
 *    Brother Kirby, CS 235
 * Author:
 *    Rolando Rodriguez & Jatsiri Martinez
 * Summary:
 *    This program will implement the Selection Sort
 ************************************************************************/

#ifndef SORT_SELECTION_H
#define SORT_SELECTION_H

/*****************************************************
 * SORT SELECTION
 * Perform the selection sort
 ****************************************************/

template <class T>
void sortSelection(T array[], int num)
{
	//The outer loop will go through n iterations. iPivot refers to the right most slot
	for (int iPivot = num-1; iPivot >=1; iPivot--)
	{
		int iLargest = 0; //representing the largest element found thus far

		//The inner loop will execute n times from the outer loop and will increment iPivot times.
		//representing the index in the unsorted side of the array that is currently being searched
		for (int iCheck = 1; iCheck <= iPivot-1; iCheck++)
		{
			if (array[iLargest] < array[iCheck]) //every time iLargest is less tha iCheck
				iLargest = iCheck; // assign iCheck to iLargest
		}
		if (array[iLargest] > array[iPivot]) //if iLargest is greater tha iPivot
			swap(&array[iLargest], &array[iPivot]); //swap the values
	}
}


#endif // SORT_SELECTION_H
