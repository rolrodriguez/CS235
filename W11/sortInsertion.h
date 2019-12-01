/***********************************************************************
 * Module:
 *    Week 11, Sort Insertion
 *    Brother Helfrich, CS 235
 * Author:
 *    Rolando Rodriguez & Jatsiri Martinez
 * Summary:
 *    This program will implement the Insertion Sort
 ************************************************************************/

#ifndef SORT_INSERTION_H
#define SORT_INSERTION_H

#include <cassert>

/*****************************************************
 * BINARY SEARCH
 * Return the locaion of iInsert
 ****************************************************/
template <class T>
int binarySearch(T array[], T search, int iBegin, int iEnd)
{
	// Find the mid point of the array
	int iMiddle = (iBegin + iEnd) / 2;
	if (iBegin > iEnd)
		return iBegin;
	// If the mid point is equal to the value, then we are done
	if (array[iMiddle] == search)
		return iMiddle;
	// Recursive section, if the values are higher than the mid point
	// continue with the second half
	if (search > array[iMiddle])
		return binarySearch(array, search, iMiddle + 1, iEnd);
	// Otherwise continue with the first half 
	else
		return binarySearch(array, search, iBegin, iMiddle - 1);
}

/***********************************************
* SORT INSERTION
* Perform the insertion sort
****************************************************/
template <class T>
void sortInsertion(T array[], int num)
{
	//will start at right - most slot(iPivot = num - 1) and moves left.
	for (int iPivot = num-2; iPivot >= 0; iPivot--)
	{
		//The location of the new slot for array[iPivot] needs to be found. We will call this iInsert.
		T valuePivot = array[iPivot];
		int iShift;
		
		//Everything that is currently between iPivot + 1 and iInsert needs to be scooted over to the left by one slot.
		//The value that was under iPivot needs to be inserted into the new location iInsert
		int iInsert = binarySearch(array, valuePivot, iPivot + 1, num - 1);
		iInsert--;

		//each shift will move half of the sorted side of the pivot.
		for ( iShift = iPivot; iShift < iInsert; iShift++)
			array[iShift] = array[iShift + 1];
		array[iShift] = valuePivot;

	}

}




#endif // SORT_INSERTION_H
