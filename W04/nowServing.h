/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This will contain just the prototype for nowServing(). You may
 *    want to put other class definitions here as well.
 * Author:
 *    Jatsiri Martínez and Rolando Rodriguez
 ************************************************************************/

#ifndef NOW_SERVING_H
#define NOW_SERVING_H

#include "deque.h" // for DEQUE
//#include <vector>
#include "student.h"

class NowServing
{

private:
   Student currentStudent;
   custom::deque<Student> studentLine;
   bool isServing;

public:
   NowServing() : isServing(false) {}
   void setCurrentStudent(Student current)
   {
      currentStudent = current;
      isServing = true;
   }
   void serveStudent();
   Student getCurrentStudent() const { return currentStudent; }
   void clearStudent() { isServing = false; }

   void setDeque(custom::deque<Student> student) { studentLine = student; }
   custom::deque<Student> &getDeque() { return studentLine; }
   bool getIsServing() const { return isServing; }
};
// the interactive nowServing program
void nowServing();
#endif // NOW_SERVING_H
