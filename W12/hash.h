#include<iostream>
#include "list.h"

#ifndef HASH_H
#define HASH_H

using namespace custom;
/*****************************************
* HASH CLASS
******************************************/
template <class T>
class Hash
	{
	private:
           // Pointer to an array of lists   
           list <T> * table;
           
           // Number of elements in the hash
           int numElements;
 
           // Number of categories to divide the data by
           int numBuckets;
           
	public:
           // DEFAULT CONSTRUCTOR: set Buckets and elements to zero
           Hash() : numBuckets(0), numElements(0), table(NULL) {}

           // NON-DEFAULT CONSTRUCTOR: define number of buckets
           // and allocate array of lists
           Hash(int numBuckets)
           {
              this->numBuckets = numBuckets;
              numElements = 0;
              table = new list<T>[numBuckets];
           }
           // COPY CONSTRUCTOR 
           Hash(const Hash & rhs)
           {
              if (rhs.size() == 0)
              {
                 numElements = 0;
                 numBuckets = rhs.numBuckets;
                 table = NULL;
                 return;
              }
              else
                 table = new list<T>[rhs.numBuckets];
              
              this->numBuckets = rhs.numBuckets;
              this->numElements = rhs.numElements;
              
              for (int i = 0; i < numBuckets; i++)
                 this->table[i] = rhs.table[i];
              
           }
           // DESTRUCTOR
           ~Hash() { clear(); }
           
           //ASSIGNMENT OPERATOR
           Hash & operator =(const Hash & rhs);
           
           //STANDARD CONTAINER INTERFACES
           int size()const { return numElements; }// Returns the number of elements in the Hash.
           int capacity()const { return numBuckets; } //Returns the number of buckets in the Hash.
           bool empty() { return numElements == 0; } // Determines whether the current Hash is empty.
           void clear() { numElements = 0; }//Clear the contents
           bool find(const T & t); //Returns true if the value is found, false otherwise.
           void insert(const T &t); // Places a new instance of a value in the Hash.
           
           // PURE VIRTUAL HASH FUNCTION: is implemented by inheriting classes
           virtual int hash(const T &t) const = 0;
	};

	/*****************************************************
	* Assignment Operator
	* Copy one Hash into another and returns it
	******************************************************/
	template <class T>
	Hash <T> & Hash<T> :: operator = (const Hash & rhs)
	{
           //if there is no elements in rhs, do nothing
           if (rhs.size() == 0)
           {
              numElements = 0;
              numBuckets = rhs.numBuckets;
              table = NULL;
              return *this;
           }
           else
           {
              table = new list<T>[rhs.numBuckets];
           }
           // copy the rhs numElements,buckets and table to the current elements,
           // buckets and table
           this->numElements = rhs.numElements;
           this->numBuckets = rhs.numBuckets;
           
           for (int i = 0; i < numBuckets; i++)
              table[i] = rhs.table[i];
           
           return *this;
	}

/******************************************************
 * insert()
 * Places a new instance of a value in the Hash. 
 * The parameter is the elements to be inserted.
 *******************************************************/
template <class T>
void Hash<T>::insert(const T &t)
{
   int i = hash(t);
   table[i].push_back(t);
   numElements++;
}
/******************************************************
 * find()
 *  The parameter is the value to be found. 
 *  Returns true if the value is found, false otherwise.
 ********************************************************/
template <class T>
bool Hash<T>::find(const T & t)
{
   int i = hash(t);
   
   if (table[i].find(t) == NULL)
      return false;
   else
      return true;
}


#endif
