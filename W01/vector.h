/***********************************************************************
 * Header:
 *    vector
 * Summary:
 *    This class contains the notion of a vector:
 *    a container for other elements. This 
 *    container size increases to hold the 
 *    elements by doubling its size. This file
 *    uses the template originally written
 *    by Br. Helfrich.
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Rolando Rodriguez
 ************************************************************************/

#ifndef vector_H
#define vector_H

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
 * vector
 * A class for an variable size container
 * that holds objects
 ***********************************************/
template <class T>
class vector
{
public:
   // constructors and destructors
   vector();
   vector(int numElements);
   vector(int numElements, T element);
   vector(const vector & rhs);
  ~vector()                         { delete [] array;   }
   vector & operator = (const vector & rhs);
   
   // standard container interfaces
   int  size()     const { return numElements;                 }
   int  capacity() const { return numCapacity;                 }
   bool empty() const { return numElements == 0;               }
   void clear() { numElements = 0;                             }
   void push_back(T element);

   // vector-specific interfaces
   // what would happen if I passed -1 or something greater than numElements?
   T & operator [] (int index)
   {
      return array[index];
   }
   const T & operator [] (int index) const 
   {
      return array[index];
   }
   
   // the various iterator interfaces
   class iterator;
   class const_iterator;
   iterator begin()      { return iterator (array); }
   iterator end()        { return iterator (array + numElements);};
   const_iterator cbegin() const { return const_iterator(array);}
   const_iterator cend() const { return const_iterator (array + numElements);};

   // a debug utility to display the vector
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   T * array;                 // dynamically allocated vector of T
   int numElements;           // Elements in the vector
   int numCapacity;           // Current storage capacity
   void reallocate(int size); // Helper function to resize the array
};

/**************************************************
 * vector ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class vector <T> :: iterator
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
   // pointer to element
   T * p;
};

/**************************************************
 * vector CONSTANT ITERATOR
 * A constant iterator through vector
 *************************************************/
template <class T>
class vector <T> :: const_iterator
{
public:
   // constructors, destructors, and assignment operator
   const_iterator()      : p(NULL){              }
   const_iterator(T * p) : p(p)         {              }
   const_iterator(const const_iterator & rhs) { *this = rhs; }
   const_iterator & operator = (const const_iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
   T & operator * () { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   const_iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // prefix decrement
   const_iterator & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix increment
   const_iterator operator ++ (int postfix)
   {
      const_iterator tmp(*this);
      p++;
      return tmp;
   }
   // postfix decrement
   const_iterator operator -- (int postfix)
   {
      const_iterator tmp(*this);
      p--;
      return tmp;
   }

   private:
   // pointer to element
   T * p;
};

/*******************************************
 * vector :: Assignment
 * 
 * Operator to assign a vector to other:
 * 1) Sizes the recently created vector
 * to the size of the one been copied.
 * 2) Go through each element and copies
 * it into the new vector
 * 3) Returns the freshly copied vector
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
{
   // Attempt to allocate to memory
   // equalize size and capacity
   try{
      array = new T[rhs.numCapacity];
      numCapacity = rhs.numCapacity;
      numElements = rhs.numElements;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer for vector";
   }
   
   for (int i = 0; i < numElements; i++)
      array[i] = rhs.array[i];
   
   return *this;
}

/*******************************************
 * vector :: DEFAULT CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector()
{
   array = NULL;
   numElements = 0;
   numCapacity = 0;
}

/*******************************************
 * vector :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(const vector <T> & rhs) 
{
   assert(rhs.numElements >= 0);
   // do nothing if there is nothing to do
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
      throw "ERROR: Unable to allocate buffer for vector";
   }
   
   // copy over the capacity
   numCapacity = rhs.numCapacity;
   numElements = rhs.numElements;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      array[i] = rhs.array[i];
}

/**********************************************
 * vector : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity" full
 * with the default value of 0
 **********************************************/
template <class T>
vector <T> :: vector(int numElements) 
{
   assert(numElements >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an vector, this is kinda pointless
   if (numElements == 0)
   {
      this->numElements = 0;
      this->numCapacity = 0;
      this->array = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      array = new T[numElements];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the stuff
   this->numElements = numElements;
   this->numCapacity = numElements;

   // Fill the vector with the default value of 0
   for (int i = 0; i < numElements; i++){
      array[i] = 0;
   }   
}

/**********************************************
 * vector : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity" and
 * append one element
 **********************************************/

template <class T>
vector <T> :: vector(int numElements, T element){
   this = vector(numElements);
   this->push_back(element);
} 

/********************************************
 * vector : DISPLAY
 * A debug utility to display the contents of the vector
 *******************************************/
template <class T>
void vector <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "vector<T>::display()\n";
   std::cerr << "\tnumElements = " << numElements << "\n";
   for (int i = 0; i < numElements; i++)
      std::cerr << "\tdata[" << i << "] = " << array[i] << "\n";
#endif // NDEBUG
}

/********************************************
 * vector : reallocate
 * Increases the size of the array in the
 * vector container to the number specified
 * by newSize
 *******************************************/

template <class T>
void vector <T> :: reallocate(int newSize){

   T * bufferNew = new T[newSize]; 
   if (NULL == bufferNew) 
   { 
      std::cout << "Unable to allocate a buffer of size " << newSize << std::endl; 
      return;
   } 
   int i; 
   for (i = 0; i < this->size(); i++) // use index because it is easier 
      bufferNew[i] = array[i]; // than two pointers 
    
   delete [] array; // return the new buffer 
   array = bufferNew;
   return;
}


/********************************************
 * vector : push_back
 * 
 * Adds a new element to the back of the 
 * vector. If the vector is empty it 
 * creates one space to add the new element.
 * If the element has space will add it to
 * it. If the element needs extra capacity
 * will call the reallocate function to
 * increase the capacity of the vector.
 ********************************************/
template <class T>
void vector <T> :: push_back(T element){
   // if vector is empty add capacity and add element
   if (this->empty())
   {
      try
      {
         array = new T[1];
      }
      catch (std::bad_alloc)
      {
         throw "Unable to allocate a new buffer for vector";
      }

      array[numElements] = element;
      numElements++;
      numCapacity++;
   }
   else
   {
      if (numElements == numCapacity)
      {
         numCapacity *= 2;
         reallocate(numCapacity);
         
      }
      array[numElements] = element;
      numElements++;
   }
   
}

}; // namespace custom

#endif // vector_H

