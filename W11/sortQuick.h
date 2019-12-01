/***********************************************************************
 * Module:
 *    Week 11, Sort Quick
 *    Brother Kirby, CS 235
 * Author:
 *    Rolando Rodriguez & Jatsiri Martinez
 * Summary:
 *    This program will implement the Quick Sort
 ************************************************************************/

#ifndef SORT_QUICK_H
#define SORT_QUICK_H

/*****************************************************
 * SORT QUICK
 * Perform the quick sort
 ****************************************************/
template <class T>
void sortQuick(T array[], int num)
{
	// If there is only one element nothing is required
	if (num <= 1)
		return;

	int iEnd = num - 1;
	int iDown = iEnd;
	int iUp = 0;
	// make the pivot value the mid element
	T pivotValue = array[iEnd / 2];

	while (iUp <= iDown)
	{
		while (iUp <= iEnd && pivotValue > array[iUp])
			iUp++;
		while (iDown >= 0 && array[iDown] > pivotValue)
			iDown--;
		if (iUp <= iDown)
			swap(array[iUp++], array[iDown--]);
	}

	sortQuick(array, iUp);
	sortQuick(array + iUp, iEnd - iUp + 1);
}

#endif // SORT_QUICK_H
