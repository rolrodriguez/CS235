

#include "deque.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
using std ::string;

#ifndef STUDENT_H
#define STUDENT_H

class Student
{
private:
   string className;
   string name;
   int time;
   bool emergency;
   string studentText;

public:
   Student() : time(0), emergency(false) {}
   Student(string student)
   {
      studentText = student;

      std::stringstream ss(student);
      string word;

      ss >> word;

      if (word == "!!")
      {
         emergency = true;
         ss >> word;
         className = word;
      }
      else
      {
         className = word;
         emergency = false;
      }

      ss >> word;
      name = word;

      ss >> word;
      time = atoi(word.c_str());
   }
   int getTime() const { return time; }
   string getName() const { return name; }
   string getClass() const { return className; }
   bool isEmergency() const { return emergency; }
   void gettingHelp() { time--; }
   string getStudentText() const { return studentText; }
};

#endif
