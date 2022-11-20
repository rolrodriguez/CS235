/***********************************************************************
* Header:
*    Queue     
* Summary:
*    This contains the prototypes and implementation of the queue class.
*    This class is similar to the STL version on std::queue
* Author
*    Jatsiri Detzani and Rolando Rodriguez
************************************************************************/
#include <cassert>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#ifndef QUEUE_H
#define QUEUE_H

namespace custom
{

template <class T>
class queue
{

public:
   // constructors and destructors
   queue();
   queue(int numCapacity);
   queue(const queue &rhs);
   ~queue() { delete[] array; }
   queue &operator=(const queue &rhs);

   // standard container interfaces
   int size() const { return numPush - numPop; }
   int capacity() const { return numCapacity; }
   bool empty() const { return size() == 0; }
   void clear()
   {
      numPush = 0;
      numPop = 0;
      numCapacity = 0;
   }
   void push(T element);
   void pop();

   // Returns the element currently at the end of the queue
   // if the queue is currently empty, throws an error
   T &front()
   {
      if (!empty())
      {
         return array[iHead()];
      }
      else
      {
         throw "ERROR: Unable to reference the element from an empty queue";
      }
   }
   const T &front() const
   {
      if (!empty())
      {
         return array[iHead()];
      }
      else
      {
         throw "ERROR: Unable to reference the element from an empty queue";
      }
   }

   T &back()
   {
      if (!empty())
      {
         return array[iTail()];
      }
      else
      {
         throw "ERROR: Unable to reference the element from an empty queue";
      }
   }
   const T &back() const
   {
      if (!empty())
      {
         return array[iTail()];
      }
      else
      {
         throw "ERROR: Unable to reference the element from an empty queue";
      }
   }

private:
   T *array; // dynamically allocated queue of T

   int numCapacity;       // Current storage capacity
   void resize(int size); // Helper function to resize the array
   int numPush;
   int numPop;
   int iTail() const { return (numPush - 1) % numCapacity; }
   int iHead() const { return numPop % numCapacity; }

}; // queue class

/**********************************************************
 * queue :: push()
 * Adds an element to the queue.
 * If the queue is full,the capacity will be doubled
 **********************************************************/
template <class T>
void queue<T>::push(T element)
{

   if (numCapacity == 0)
   {
      resize(++numCapacity);
   }

   else if (size() == numCapacity)
   {
      resize(numCapacity *= 2);
   }

   numPush++;

   array[iTail()] = element;
}

/**********************************************************
  * queue :: pop()
 * Removes an element at the end of the queue.
 * Reduces the size by one
 **********************************************************/
template <class T>
void queue<T>::pop()
{
   if (!empty())
   {
      numPop++;
   }
}

/*******************************************
 * queue :: Assignment
 * 
 * Operator to assign a queue to other:
 * 1) Sizes the recently created queue
 * to the size of the one been copied.
 * 2) Go through each element and copies
 * it into the new queue
 * 3) Returns the freshly copied queue
 *******************************************/
template <class T>
queue<T> &queue<T>::operator=(const queue<T> &rhs)
{

   if (rhs.numCapacity == 0)
   {
      array = NULL;
      numCapacity = 0;
      numPop = 0;
      numPush = 0;
      return *this;
   }

   try
   {
      array = new T[rhs.numCapacity];
      numCapacity = rhs.numCapacity;
      numPop = rhs.numPop;
      numPush = rhs.numPush;
   }
   catch (std::bad_alloc)
   {
      throw "error: unable to allocate";
   }

   if (numCapacity < rhs.size())
      resize(rhs.size());

   for (int i = numPop; i < numPush; i++)
   {
      array[i % numCapacity] = rhs.array[i % rhs.numCapacity];
   }

   return *this;
}

/*******************************************
 * queue :: DEFAULT CONSTRUCTOR
 *******************************************/
template <class T>
queue<T>::queue()
{
   array = NULL;
   numPop = 0;
   numPush = 0;
   numCapacity = 0;
}

/*******************************************
 * queue :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
queue<T>::queue(const queue<T> &rhs)
{
   // do nothing if there is nothing to do
   if (rhs.capacity() == 0)
   {
      numCapacity = 0;
      numPop = 0;
      numPush = 0;
      array = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      array = new T[rhs.capacity()];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer for queue";
   }

   // copy over the capacity

   numPop = rhs.numPop;
   numPush = rhs.numPush;
   numCapacity = rhs.numCapacity;
   // copy the items over one at a time using the assignment operator
   for (int i = rhs.numPop; i < rhs.numPush; i++)

      array[i % numCapacity] = rhs.array[i % rhs.numCapacity];
}

/**********************************************
 * queue : NON-DEFAULT CONSTRUCTOR
 * Presize
 the queue to "capacity" full
 * with the default value of 0
 **********************************************/
template <class T>
queue<T>::queue(int numCapacity)
{

   // do nothing if there is nothing to do.
   // since we can't grow an queue, this is kinda pointless
   if (numCapacity == 0)
   {
      this->numPop = 0;
      this->numPush = 0;
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
   this->numPop = 0;
   this->numPush = 0;
}

/********************************************
 * queue : resize

 * Increases the size of the array in the
 * queue container to the number specified
 * by newSize
 *******************************************/

template <class T>
void queue<T>::resize(int newSize)
{
   // Allocate a new array
   T *bufferNew = new T[newSize];

   if (bufferNew == NULL)
   {
      std::cout << "Unable to allocate a buffer of size " << newSize << std::endl;
      return;
   }

   for (int i = 0; i < size(); i++)

      bufferNew[i % numCapacity] = array[i % numCapacity];

   delete[] array; // return the new buffer

   array = bufferNew;
   numCapacity = newSize;
   return;
}

}; //namespace custom

#endif