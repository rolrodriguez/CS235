/***********************************************************************
 * Implementation:
 *    WholeNumber
 * Summary:
 *    This will contain the implementation for the WholeNumber class 
 * Author
 *    Jatsiri Detzani and Rolando Rodriguez
 **********************************************************************/

#include "wholeNumber.h"

/*******************************************
 * list :: operator +=
 *
 * Add and assign the sum
 *
 * Parameters:
 *      rhs: wholenumber to be added with
 * Returns:
 *      Sum of the two numbers
 *******************************************/
WholeNumber & WholeNumber::operator+=(WholeNumber & rhs)
{
  // list to hold the sum of each element
  list<int> sum;

  // iterator to go through the elements of the current number
  list<int>::reverse_iterator it = digits.rbegin();

  // iterator to go through the elements of the number to add
  list<int>::reverse_iterator itRHS = rhs.digits.rbegin();
  
  // integer to keep the carryon from each sum
  int carryOnNum = 0;

  // left number
  int left = 0;

  // right number
  int right = 0;

  // To temporarily hold the result
  int result =0;
  
  // Go through each list in reverse until the end
  while (it != digits.rend() || itRHS != rhs.digits.rend())
  {
    // set the left number from the iterator
    if (it != digits.rend())
    {
      left = *it;
      it++;
    }
    // if this is the end set value to zero
    else
    {
      left = 0;
    }
    
    // set the right number from the iterator
    if (itRHS != rhs.digits.rend())
    {
      right = *itRHS;
      itRHS++;
    }
    // if this is the end set value to zero
    else
    {
      right = 0;
    }
    // the sum value is the sum of left, right and any carryon
    int tempValue = left + right + carryOnNum;

    // the result should only keep the last three digits
    result = tempValue % 1000;

    // the remaining numbers are carryon
    carryOnNum = tempValue / 1000;

    // push the result to the front to build the sum
    sum.push_front(result);
  }
  // if there is any carryon left push to the front
  if (carryOnNum > 0)
    sum.push_front(carryOnNum);
  digits = sum;
  return *this;
}

/*******************************************
 * list :: operator =
 *
 * Assing a number to other
 *
 * Parameters:
 *      rhs: wholenumber to be assigned
 * Returns:
 *      this instance with the contents
 *      of rhs.
 *******************************************/
WholeNumber & WholeNumber::operator=(const WholeNumber & rhs)
{
  digits = rhs.digits;
  return *this;
}
