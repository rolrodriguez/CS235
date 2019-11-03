/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    Jatsiri Detzani and Rolando Rodriguez
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
#include "wholeNumber.h" // for WHOLENUMBER
using namespace std;


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first several Fibonacci numbers
   int number;
   int count = 0;
   // Use WholeNumber class in the case big numbers are entered
   WholeNumber a(0);
   WholeNumber b(1);
   WholeNumber c(1);

   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   // your code to display the first <number> Fibonacci numbers
   while(count < number)
   {
      c = a;
      c += b;
      a = b;
      b = c;
      cout << "\t" << a << endl;
      count++;
   }

   WholeNumber x(0);
   WholeNumber y(1);
   WholeNumber z(1);

   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;
   count = 0;
   // your code to display the <number>th Fibonacci number
   while(count < number)
   {
      z = x;
      z += y;
      x = y;
      y = z;
      count++;
   }
   cout << "\t" << x << endl;
}


