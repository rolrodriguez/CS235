/***********************************************************************
* Header:
*    STACK     
* Summary:
*    This contains the prototypes and implementation of the stack class.
*    This class is similar to the STL version on std::stack
* Author
*    Jatsiri Detzani and Rolando Rodriguez
************************************************************************/
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#ifndef STACK_H
#define STACK_H

namespace custom
{
template <class T>
class stack // Stack class starts
{

public:
   // constructors and destructors
   stack();
   stack(int numCapacity);
   stack(const stack &rhs);
   ~stack() { delete[] array; }
   stack &operator=(const stack &rhs);

   // standard container interfaces
   int size() const { return numElements; }
   int capacity() const { return numCapacity; }
   bool empty() const { return numElements == 0; }
   void clear() { numElements = 0; }
   void push(T element);
   void pop();
   // Top as a setter
   T &top() throw(const char *)
   {
      if (!empty())
      {
         return array[size() - 1];
      }
      else
      {
         throw "ERROR: Unable to reference the element from an empty Stack";
      }
   }
   // Top as a getter
   const T &top() const throw(const char *)
   {
      if (!empty())
      {
         return array[size() - 1];
      }
      else
      {
         throw "ERROR: Unable to reference the element from an empty Stack";
      }
   }

   // stack-specific interfaces
   // what would happen if I passed -1 or something greater than numElements?
   T &operator[](int index)
   {
      return array[index];
   }
   const T &operator[](int index) const
   {
      return array[index];
   }

private:
   T *array;              // dynamically allocated stack of T
   int numElements;       // Elements in the stack
   int numCapacity;       // Current storage capacity
   void resize(int size); // Helper function to resize the array

}; // stack class

template <class T>
void stack<T>::push(T element)
{
   // Increase capacity to 1 if a new element is to be added
   if (capacity() == 0)
   {
      resize(++numCapacity);
   }
   // If the stack is full double the capacity when
   // a new element is to be added
   else if (size() == capacity())
   {
      resize(numCapacity *= 2);
   }
   // Put the element on the last position
   array[numElements++] = element;
}

template <class T>
void stack<T>::pop()
{
   // If the array is not empty remove an element
   // otherwise do nothing
   if (!empty())
   {
      resize(--numElements);
   }
}

/*******************************************
 * stack :: Assignment
 * 
 * Operator to assign a stack to other:
 * 1) Sizes the recently created stack
 * to the size of the one been copied.
 * 2) Go through each element and copies
 * it into the new stack
 * 3) Returns the freshly copied stack
 *******************************************/
template <class T>
stack<T> &stack<T>::operator=(const stack<T> &rhs)
{
   // Attempt to allocate to memory
   // equalize size and capacity
   try
   {
      array = new T[rhs.numCapacity];
      numCapacity = rhs.numCapacity;
      numElements = rhs.numElements;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer for stack";
   }

   for (int i = 0; i < numElements; i++)
      array[i] = rhs.array[i];

   return *this;
}

/*******************************************
 * stack :: DEFAULT CONSTRUCTOR
 *******************************************/
template <class T>
stack<T>::stack()
{
   array = NULL;
   numElements = 0;
   numCapacity = 0;
}

/*******************************************
 * stack :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
stack<T>::stack(const stack<T> &rhs)
{
   // Do nothing if the elements are none
   if (rhs.numElements == 0)
   {
      numElements = 0;
      array = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      array = new T[rhs.numElements];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer for stack";
   }

   // copy over the capacity and number of elements
   numCapacity = rhs.numCapacity;
   numElements = rhs.numElements;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      array[i] = rhs.array[i];
}

/**********************************************
 * stack : NON-DEFAULT CONSTRUCTOR
 * Presize
 * the stack to "capacity" full
 **********************************************/
template <class T>
stack<T>::stack(int numCapacity)
{
   // do nothing if there is nothing to do.
   // since we can't grow an stack, this is kinda pointless
   if (numCapacity == 0)
   {
      this->numElements = 0;
      this->numCapacity = 0;
      this->array = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      array = new T[numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // assign values
   this->numCapacity = numCapacity;
   this->numElements = 0;
}

/********************************************
 * stack : resize

 * Increases the size of the array in the
 * stack container to the number specified
 * by newSize
 *******************************************/

template <class T>
void stack<T>::resize(int newSize)
{
   // Allocate a new array
   T *bufferNew = new T[newSize];
   if (NULL == bufferNew)
   {
      std::cout << "Unable to allocate a buffer of size " << newSize << std::endl;
      return;
   }
   int i;
   for (i = 0; i < numElements; i++)
      bufferNew[i] = array[i];

   delete[] array; // return the new buffer
   numCapacity = newSize;
   array = bufferNew;
   return;
}

}; //namespace custom

#endif