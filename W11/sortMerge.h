/***********************************************************************
 * Module:
 *    Week 11, Sort Merge
 *    Brother Kirby, CS 235
 * Author:
 *    Rolando Rodriguez & Jatsiri Martinez
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

using namespace std;

/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void merge(T destination[], T source1[], int size1, T source2[], int size2)
{
	int i1 = 0;
	int i2 = 0;

	// Go through each sub array
	for (int iDestination = 0; iDestination < (size1 + size2); iDestination++)
	{
		// Put first elements from source1 if these are lower
		if (i1 < size1 && (i2 == size2 || source1[i1] < source2[i2]))
		{

			destination[iDestination] = source1[i1++];
		}
	  // Put values from source2 otherwise 
		else
		{

			destination[iDestination] = source2[i2++];
		}
	}
}

template <class T>
void sortMerge(T array[], int num)
{
	// Pointer to array
	T *source = array;
	// Pointer to destination array, where sorted values will be stored
	T *destination = new T[num];

	// iterations counter
	int numIterations = 0;

	// Sub array indexes
	int iBegin2 = 0;
	int iEnd1 = 0;
	int iEnd2 = 0;

	do
	{
		// Pointer to the current position within the destination array
		T *pStart = destination;
		numIterations = 0;
		// Start the first sub-array from the beginning
		int iBegin1 = 0;

		
		while (iBegin1 < num)
		{
			numIterations++;

			// Increment iEnd1 while the next element is higher than the previous one
			for (iEnd1 = iBegin1 + 1; iEnd1 < num && !(source[iEnd1 - 1] > source[iEnd1]); iEnd1++);

			// Subtract one to exclude the items that are lower
			iEnd1--;
			iBegin2 = iEnd1 + 1;

			// Increment iEnd2 while the next element is higher thant the previous one
			for (iEnd2 = iBegin2 + 1; iEnd2 < num && !(source[iEnd2 - 1] > source[iEnd2]); iEnd2++);

			// Subtract one to exclude the items that are lower
			iEnd2--;

			// If the first sub-array covers the complete word
			if (iEnd1 - iBegin1 + 1 >= num)
			{	
				// It means the sort is complete
				numIterations = 0;
				std::swap(source, destination);
				break;
			}
			// If there is a second sub-array we will need merging
			if (iBegin2 < num)
			{

				merge(pStart,
							source + iBegin1, iEnd1 - iBegin1 + 1,
							source + iBegin2, iEnd2 - iBegin2 + 1);
				// Reassign pStart to a new location to continue in sequence
				pStart = pStart + (iEnd1 - iBegin1 + iEnd2 - iBegin2 + 2);
			}
		 	// If there is not we need to start again to make sure we skimmed through the array
			else
			{
				// Store last values from source to destination without a complete merge
				for (int i = 0; i <= iEnd1 - iBegin1; i++)
					pStart[i] = *(source + iBegin1 + i);
				// Set to -1 so iBegin can return to zero
				iEnd2 = -1;
				std::swap(source, destination);
				// Re-start pStart pointer within destination
				pStart = destination;
			}

			iBegin1 = iEnd2 + 1;
		}

		std::swap(source, destination);
	// Repeat if at least one internal iteration is needed
	} while (numIterations > 1);

	// Copy values from source array to the original array
	if (array != source)
	{
		for (int i = 0; i <= num - 1; i++)
			array[i] = source[i];
	}
}

#endif // SORT_MERGE_H
