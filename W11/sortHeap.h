/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Kirby, CS 235
 * Author:
 *    Rolando Rodriguez & Jatsiri Martinez
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H
using namespace std;
#define MIN 1
template <class T>
class Heap
{
public:
	// Heap non-default constructor, it does heapify the array
	Heap(T *arrayInput, int numInput)
	{
		this->array = arrayInput;
		this->num = numInput;
		// Percolates down the heap
		for (int index = num / 2 - 1; index >= 0; index--)
			percolateDown(index);
	}

	void sort();
	

private:
	// Array of T type
	T *array;
	// Number of elements in the array
	int num;

	// Convert call percolate Down to heapify the array
	void heapify()
	{
		for (int i = (num / 2) - 1; i >= 0; i--)
			percolateDown(i);
	}

	// Organize the array in a heap
	void percolateDown(int index)
	{
		// Assign left and right indexes
		int indexLeft = index * 2 + 1;
		int indexRight = indexLeft + 1;

		// if the right index element value is higher then swap with root
		if (indexRight < num &&
			array[indexRight] > array[indexLeft] &&
			array[indexRight] > array[index])
		{
			swap(index, indexRight);
			percolateDown(indexRight);
		}
		// if the else index element value is higher then swap with root
		else if (indexLeft < num && array[indexLeft] > array[index])
		{
			swap(index, indexLeft);
			percolateDown(indexLeft);
		}
		// else do nothing
	}

	// Swap values given two indexes in the array
	void swap(int i1, int i2) {
		T temp = array[i1];
		array[i1] = array[i2];
		array[i2] = temp;
	}
};

// Sort the array by reorganizing the heap after removing the max value
template <class T>
void Heap<T>::sort()
{
	while (num > MIN)
	{
		// Swap the max with the min value after percolation
		swap(0, num-1);
		// Eliminate the max value from the element count
		num--;
		// Percolate again to index 0
		percolateDown(0);
	}
}

/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>
void sortHeap(T array[], int num)
{
	Heap<T> h(array, num);
	h.sort();
}


#endif // SORT_HEAP_H
