/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Rolando Rodriguez and Jatsiri Martinez
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   int i; // iteration index
   T key; // key for comparisons
   
   for(int j = 1; j < num; j++)
   {
      key = array[j];
      i = j - 1;

      // move lower numbers to lower positions in array comparing to key
      while(i >= 0 && array[i] > key)
      {
         array[i + 1] = array[i];
         i = i - 1;
      }
      // relocate key value in array
      array[i + 1] = key;
   }
         
}

#endif // INSERTION_SORT_H

