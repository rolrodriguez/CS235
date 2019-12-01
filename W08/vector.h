/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This class contains the notion of an array: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * ARRAY
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
   // constructors and destructors
   Vector(){numElements = 0; numCapacity = 0; data = NULL; }
   Vector(int numElements)     throw(const char *);
   Vector(const Vector & rhs)  throw(const char *);
  ~Vector()                         { delete [] data;   }
  //operator =
   Vector & operator = (const Vector & rhs)  throw(const char*);

   // standard container interfaces
   int  size()     const { return numElements;                 }
   int  capacity() const { return numCapacity;                 }  
   bool empty() {
     if (numElements == 0)
       return false;
     else
       return true ;
   }
   void clear() { numElements = 0; }
   

   void push_back(const T & t) throw (const char *)
   {
      if(t == numCapacity)
         numCapacity *= 2;

   }
   
   // array-specific interfaces
   // what would happen if I passed -1 or something greater than num?
   
   
   T & operator [] (int index) throw(const char *)
   {
      if(index > numElements)
	 throw "ERROR: Invalid Index";
      return data[index];
   }
   const T & operator [] (int index) const throw(const char *)
   {
     if(index > numElements)
	 throw "ERROR: Invalid Index";
      return data[index];
   }
   
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();

   // a debug utility to display the array
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   T * data;              // dynamically allocated array of T
   int numCapacity;      // both the capacity and the number of elements
   int numElements;
};

/**************************************************
 * ARRAY ITERATOR
 * An iterator through array
 *************************************************/
template <class T>
class Vector <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }
   // prefix decrement
   iterator & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }

    // postfix decrement
   iterator operator -- (int postfix)
   {
      iterator tmp(*this);
      p--;
      return tmp;
   }
private:
   T * p;
};


/********************************************
 * ARRAY :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename Vector <T> :: iterator Vector <T> :: end ()
{
   return iterator (data + numElements);
}

/*******************************************
 * ARRAY :: Assignment
 *******************************************/
template <class T>
Vector <T> & Vector <T> :: operator = (const Vector <T> & rhs) throw(const char*)
{
   // we can only copy arrays of equal size. Vectors are not this way!
   if (rhs.size() != size())
   {
      throw "ERROR: Unable to copy arrays of different sizes";
   }

   assert(numElements == rhs.numElements);
   for (int i = 0; i < numElements; i++)
     this->push_back(rhs.data[i]);

   return *this;
}

/*******************************************
 * ARRAY :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
  Vector <T> :: Vector(const Vector <T> & rhs) throw(const char*)
{
   assert(rhs.numElements >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.Capacity == 0)
   {
      numCapacity = 0;
      numElements = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity
   numCapacity = rhs.numCapacity;
   numElements = rhs.numElements;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * ARRAY : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity"
 **********************************************/
template <class T>
Vector <T> :: Vector(int numElements) throw(const char*)
{
   assert(numCapacity >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an array, this is kinda pointless
   if (numCapacity == 0)
   {
      this->numCapacity = 0;
      this->numElements = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->numCapacity = numElements;
   this->numElements = numElements;
}

/********************************************
 * ARRAY : DISPLAY
 * A debug utility to display the contents of the array
 *******************************************/
template <class T>
void Vector <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "vector<T>::display()\n";
   std::cerr << "\tnumElements = " << numElements << "\n";
   for (int i = 0; i < numElements; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // ARRAY_H

