/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Jatsiri Detzani and Rolando Rodriguez
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
   int j = 0;
   string request;
   NowServing serving;
   cin.ignore();
   do
   {
      cout << "<" << j << "> ";
      getline(cin, request);

      if (request != "finished")
      {

         Student newStudent;

         if (serving.getIsServing())
         {
            serving.serveStudent();
         }
         if (request != "none")
         {
            Student newStudent(request);
            if (newStudent.isEmergency())
            {
               serving.getDeque().push_front(newStudent);
            }
            else
            {
               serving.getDeque().push_back(newStudent);
            }
         }
         if (!serving.getIsServing())
         {
            if (!serving.getDeque().empty())
            {
               serving.setCurrentStudent(serving.getDeque().front());
               serving.getDeque().pop_front();
            }
         }

         if (serving.getIsServing())
         {

            if (serving.getCurrentStudent().isEmergency())
            {
               cout << "\tEmergency for " << serving.getCurrentStudent().getName() << " for class "
                    << serving.getCurrentStudent().getClass() << ". Time left: "
                    << serving.getCurrentStudent().getTime() << endl;
            }
            else
            {
               cout << "\tCurrently serving " << serving.getCurrentStudent().getName() << " for class "
                    << serving.getCurrentStudent().getClass() << ". Time left: "
                    << serving.getCurrentStudent().getTime() << endl;
            }
         }

         j++;
      }
   } while (request != "finished");

   // end
   cout << "End of simulation\n";
}

void NowServing::serveStudent()
{
   if (getIsServing())
   {
      currentStudent.gettingHelp();
      if (currentStudent.getTime() <= 0)
      {

         isServing = false;
      }
   }
}
