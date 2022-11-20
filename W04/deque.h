/*****************************************************
* Header:
*    Deque     
* Summary:
*    This contains the prototypes and implementation of the deque class.
*    This class is similar to the STL version on std::deque
* Author
*    Jatsiri Detzani and Rolando Rodriguez
************************************************************************/
#include <cassert>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#ifndef DEQUE_H
#define DEQUE_H

namespace custom
{

template <class T>
class deque
{

public:
   // constructors and destructors
   deque();
   deque(int numCapacity);
   deque(const deque &rhs);
   ~deque() { delete[] array; }
   deque &operator=(const deque &rhs);

   // standard container interfaces
   int size() const { return iBack - iFront + 1; }
   bool empty() const { return size() == 0; }
   void clear()
   {
      iFront = 0;
      iBack = -1;
      numCapacity = 0;
   }
   int capacity() const { return numCapacity; }
   void push_front(const T element);
   void push_back(const T element);
   void pop_front();
   void pop_back();
   T &front();
   const T &front() const;
   T &back();
   const T &back() const;

   // Returns the element currently at the end of the deque
   // if the deque is currently empty, throws an error

private:
   T *array; // dynamically allocated deque of T
   int iFront;
   int iBack;
   int numCapacity; // Current storage capacity

   void resize(int numCapacity); // Helper function to resize the array
   int iNormalize(int normalize)
   {
      if (normalize >= 0)
         return normalize % numCapacity;
      else
         return (numCapacity + (normalize % numCapacity)) % numCapacity;
   }

   int iFrontNormalize() { return iNormalize(iFront); }
   int iBackNormalize() { return iNormalize(iBack); }
}; // deque class

/**********************************************************
 * deque :: push_back()
 * Adds an element to the deque.
 * If the deque is full,the capacity will be doubled
 **********************************************************/
template <class T>
void deque<T>::push_back(const T element)
{
   // if the deque is empty, set the capacity to 1
   if (size() == 0)
   {
      resize(numCapacity + 1);
   }
   // if the deque is full, double the capacity
   else if (size() == capacity())

      resize(numCapacity * 2);

   iBack++;

   array[iBackNormalize()] = element;
}

/**********************************************************
 * deque :: push_front()
 * Adds an element to the deque.
 * If the deque is full,the capacity will be doubled
 **********************************************************/
template <class T>
void deque<T>::push_front(const T element)
{
   // if the deque is empty, set the capacity to 1
   if (size() == 0)
   {
      resize(numCapacity + 1);
   }
   // if the deque is full, double the capacity
   else if (size() == capacity())

      resize(numCapacity * 2);

   iFront--;

   array[iFrontNormalize()] = element;
}

/**********************************************************
 * deque :: pop_front()
 * Removes an element at the end of the deque.
 * Reduces the size by one
 **********************************************************/
template <class T>
void deque<T>::pop_front()
{
   if (!empty())
      iFront++;
}

/**********************************************************
 * deque :: pop_back()
 * Removes an element at the end of the deque.
 * Reduces the size by one
 **********************************************************/
template <class T>
void deque<T>::pop_back()
{
   if (!empty())
      iBack--;
}

/*******************************************
 * deque :: Assignment
 * 
 * Operator to assign a deque  to other:
 * 1) Sizes the recently created deque
 * to the size of the one been copied.
 * 2) Go through each element and copies
 * it into the new deque
 * 3) Returns the freshly copied deque
 *******************************************/
template <class T>
deque<T> &deque<T>::operator=(const deque<T> &rhs)
{
   try
   {
      array = new T[rhs.numCapacity];
      numCapacity = rhs.numCapacity;
      iFront = rhs.iFront;
      iBack = rhs.iBack;
   }
   catch (std::bad_alloc)
   {
      throw "error: unable to allocate";
   }

   if (capacity() < rhs.size())
      resize(rhs.size());

   for (int i = rhs.iFront; i <= rhs.iBack; i++)
   {
      array[iNormalize(i)] = rhs.array[iNormalize(i)];
      //push_back(rhs.array[iNormalize(i)]);
   }

   return *this;
}

/*******************************************
 * deque :: DEFAULT CONSTRUCTOR
 *******************************************/
template <class T>
deque<T>::deque()
{
   array = NULL;
   iFront = 0;
   iBack = -1;
   numCapacity = 0;
}

/*******************************************
 * deque :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
deque<T>::deque(const deque<T> &rhs)
{
   // do nothing if there is nothing to do
   if (rhs.size() == 0)
   {
      numCapacity = 0;
      iFront = 0;
      iBack = -1;
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
      throw "ERROR: Unable to allocate";
   }

   // copy over the capacity

   iFront = rhs.iFront;
   iBack = rhs.iBack;
   numCapacity = rhs.numCapacity;

   // copy the items over one at a time using the assignment operator
   for (int i = rhs.iFront; i <= rhs.iBack; i++)
   {
      array[iNormalize(i)] = rhs.array[iNormalize(i)];
      //push_back(rhs.array[iNormalize(i)]);
   }
}
/**********************************************
 * deque : NON-DEFAULT CONSTRUCTOR
 * Presize
 the deque to "capacity" full
 * with the default value of 0
 **********************************************/
template <class T>
deque<T>::deque(int numCapacity)
{

   // do nothing if there is nothing to do.
   // since we can't grow an deque, this is kinda pointless
   if (numCapacity == 0)
   {
      this->iFront = 0;
      this->iBack = -1;
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
      throw "ERROR: Unable to allocate";
   }

   // assign values
   this->numCapacity = numCapacity;
   this->iFront = 0;
   this->iBack = -1;
}

/********************************************
 * deque : resize
 *
 * Increases the size of the array in the
 * deque container to the number specified
 * by newSize
 *******************************************/

template <class T>
void deque<T>::resize(int newSize)
{

   T *bufferNew = new T[newSize];

   if (bufferNew == NULL)
   {
      std::cout << "Unable to allocate a buffer of size " << newSize << std::endl;
      return;
   }

   int j = 0;
   for (int i = iFront; i <= iBack; i++)
   {
      bufferNew[j] = array[iNormalize(i)];
      j++;
   }

   numCapacity = newSize;
   delete[] array;
   array = bufferNew;
   iFront = 0;
   iBack = j - 1;
   return;
}
template <class T>
T &deque<T>::front()
{
   if (!empty())
   {
      return array[iFrontNormalize()];
   }
   else
   {
      throw "ERROR: unable to access data from an empty deque";
   }
}
template <class T>
const T &deque<T>::front() const
{
   if (!empty())
   {
      return array[iFrontNormalize()];
   }
   else
   {
      throw "ERROR: unable to access data from an empty deque";
   }
}
template <class T>
T &deque<T>::back()
{
   if (!empty())
   {
      return array[iBackNormalize()];
   }
   else
   {
      throw "ERROR: unable to access data from an empty deque";
   }
}
template <class T>
const T &deque<T>::back() const
{
   if (!empty())
   {
      return array[iBackNormalize()];
   }
   else
   {
      throw "ERROR: unable to access data from an empty deque";
   }
}

}; //namespace custom

#endif
