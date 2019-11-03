/***********************************************************************
* Header:
*    WholeNumber
* Summary:
*    This contains the prototypes and implementation of the 
*    WholeNumber class
* Author
*    Jatsiri Detzani and Rolando Rodriguez
************************************************************************/

#ifndef WHOLENUMBER_H
#define WHOLENUMBER_H
#include "list.h"       // for LIST
#include <iomanip>      // for SETW, SETFILL
using namespace custom;

/*********************************************
 * WholeNumber class
 *
 * Class used to store large integers by the
 * usage of linked lists
 *********************************************/
class WholeNumber
{
  /******************************************* 
   *       constructors and destructors
   *******************************************/
  public:
    WholeNumber();
    WholeNumber(int number) { digits.push_front(number); }
    ~WholeNumber() {}

    /********************************************** 
     *          operator overloading
     **********************************************/

    // Addition to element and assigment (+=)
    WholeNumber & operator+=(WholeNumber & rhs);

    // Assignement (=)
    WholeNumber & operator=(const WholeNumber & rhs);

    // << operator
    friend std::ostream & operator << (std::ostream & out, WholeNumber & rhs)
    {
      list<int>::iterator it;
      // go through the complete list from the first to last
      for(it = rhs.digits.begin(); it != rhs.digits.end();++it)
      {
            // Add commas and fill the numbers if needed
            if(it != rhs.digits.begin())
              out << "," << std::setfill('0') << std::setw(3);
            out << *it;
      }
      return out;
    }
  private:
    // List of integers to hold digits from 0 to 999 each
    list<int> digits;

}; // WholeNumber
#endif