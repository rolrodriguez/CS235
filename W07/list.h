/***********************************************************************
* Header:
*    List
* Summary:
*    This contains the prototypes and implementation of the list class.
* Author
*    Jatsiri Detzani and Rolando Rodriguez
************************************************************************/

#include <iostream>

#ifndef LIST_H
#define LIST_H

namespace custom{

  /*********************************************
   * List class - List data structure
   * 
   * Collection of items implemented using
   * linked lists. Similar to STL implementation
   * in std::list
   *********************************************/
  template <class T>
  class list
  {
    public:
      /******************************************* 
       *       constructors and destructors
       *******************************************/

      // Default constructor
      list() : pHead(NULL), pTail(NULL), numElements(0) {}
      
      // Copy constructor: create a list with the same content as rhs
      list(const list<T> &rhs);
      
      // Destructor: deletes all nodes from the list
      ~list() { clear();}
     
      /******************************************* 
       *       standard container interfaces
       *******************************************/

      // boolean that shows if the list is empty
      bool empty() { return pHead == NULL; }

      // shows how many items are in the list
      int size() const { return numElements; }

      // Eliminates all elements from container
      void clear();


      /********************************************** 
       * list nested classes and iterators classes
       **********************************************/
      class Node;
      class iterator;
      class reverse_iterator;
      class const_iterator;
      class const_reverse_iterator;
      

      /******************************************* 
       *        specific list interfaces
       *******************************************/

      // insert element to the back of the list
      void push_back(const T &element);

      // insert element to the front of the list
      void push_front(const T &element);

      // remove the last element from the list
      void pop_back();

      // remove the first element from the list
      void pop_front();

      // Setter and getter versions to the first element in the list
      T & front();
      const T & front() const;

      // Setter and getter versions to the last element in the list
      T & back();
      const T & back() const;

      // returns an iterator with the position of an element in the list
      iterator find(const T &element);

      // Deletes an element, given the position in the list
      void erase(iterator & it);

      // Insert an element in the middle of the list
      iterator insert(iterator & it, const T & element);

      /********************************************** 
       *    iterators to the start and end of list
       **********************************************/
      iterator begin() { return iterator(pHead); } 
      iterator end() { return iterator(NULL); }
      reverse_iterator rbegin() { return reverse_iterator(pTail);}
      reverse_iterator rend() { return reverse_iterator(NULL); }
      const_reverse_iterator crbegin() const { return const_reverse_iterator(pTail);}
      const_reverse_iterator crend() const { return const_reverse_iterator(NULL);} 
      const_iterator cbegin() const { return const_iterator(pHead);}
      const_iterator cend() const { return const_iterator(NULL);}
      
      /********************************************** 
       *          operator overloading
       **********************************************/
      list &operator=(const list &rhs);   // assignment operator
      
    private:

      // Pointer to first node in the list
      Node * pHead;

      // Pointer to last node in the list
      Node * pTail;

      // Number of elements in the list
      int numElements;
  }; // LIST

/*******************************************
 * list :: COPY CONSTRUCTOR
 *
 * Create a copy of the rhs list
 *
 * Parameters:
 *      rhs: constant list to make the
 *      copy from.
 *******************************************/
template <class T>
list<T>::list(const list<T> &rhs)
{
  // if the list is empty only initialize the list
  if(rhs.size() == 0)
  {
    pHead = NULL;
    pTail = NULL;
    numElements = 0;
  }
  else
  { 
    // Copy the first node, its value and next node reference
    Node * currentNode = new Node(rhs.pHead->data);
    currentNode->pNext = rhs.pHead->pNext;
    // Set the first node as the head
    pHead = currentNode;
    numElements = 1;

    // If there is more than one node we need to copy the other nodes
    if(rhs.numElements > 1)
    {
      // go from the second node to the one before the last
      for (list<T>::iterator it = rhs.pHead->pNext; it != rhs.pTail; ++it)
      {
        // create new nodes, copy values and prev and next references
        Node * element = new Node(*it);
        currentNode->pNext = element;
        element->pPrev = currentNode;
        
        // update the current node with the lastest one created and 
        // increase the counter
        currentNode = element;
        numElements++;
      }

      // copy the last element of the list and make it the tail node
      Node * element = new Node(rhs.pTail->data);
      currentNode->pNext = element;
      element->pPrev = currentNode;
      pTail = element;
      numElements++;
    }
    // otherwise make this only node the tail node
    else
    {
      pTail = currentNode;
    }
    
  }
  
}

/*******************************************
 * list :: clear
 *
 * Empties the list of all elements
 *
 * Parameters:
 *      none
 * Returns:
 *      nothing
 *******************************************/
template <class T>
void list<T>::clear()
{
  // Starting from the head node delete each one
  while (pHead != NULL)
   {
      Node * pDelete = pHead;
      pHead = pHead->pNext;
      delete pDelete;
   }
   // Set list default values
   pTail = NULL;
   numElements = 0;
}

/*******************************************
 * list :: push_back
 *
 * Inserts an element into the back of the
 * list 
 *
 * Parameters:
 *      element: value to be put in the list
 * Returns:
 *      nothing
 *******************************************/
template <class T>
void list<T>::push_back(const T &element)
{
  try
  {
    // New node created to be added to the linked list 
    Node * pNew = new Node(element);

    // If the list is empty, this first node is the head and tail
    if (numElements == 0)
    {
        pHead = pNew;
        pTail = pNew;
    }
    // Otherwise this new element will become the tail
    else
    {
        // Copy references from the existing tail node
        pTail->pNext = pNew;
        pNew->pPrev = pTail;
        pTail = pNew;
    }
        
        numElements++;
  }
  catch(std::bad_alloc)
  {
    throw "ERROR: unable to allocate a new node for a list";
  }
  
  return;
}

/*******************************************
 * list :: push_front
 *
 * Inserts an element into the front of the
 * list 
 *
 * Parameters:
 *      element: value to be put in the list
 * Returns:
 *      nothing
 *******************************************/
template <class T>
void list<T>::push_front(const T &element)
{
  try
  {
    // New node created to be added to the linked list 
    Node * pNew = new Node(element);

    // If the list is empty, this first node is the head and tail
    if (numElements == 0)
    {
        pHead = pNew;
        pTail = pNew;
    }
    // Otherwise this new element will become the tail
    else
    {
      // Copy references from the existing head node
        pHead->pPrev = pNew;
        pNew->pNext = pHead;
        pHead = pNew;
    }
        numElements++;
  }
  catch(std::bad_alloc)
  {
    throw "ERROR: unable to allocate a new node for a list";
  }
  return;
  
}

/*******************************************
 * list :: pop_back
 *
 * Removes an element from the back of the 
 * list, serving to reduce the size by one
 *
 * Parameters:
 *      none
 * Returns:
 *      nothing
 *******************************************/
template <class T>
void list<T>::pop_back()
{
  if(!empty())
  {
    // Make the previous node the new tail node
    pTail->pPrev = pTail;
    numElements--;
  }

}

/*******************************************
 * list :: pop_back
 *
 * Removes an element from the front of the 
 * list, serving to reduce the size by one
 *
 * Parameters:
 *      none
 * Returns:
 *      nothing
 *******************************************/
template <class T>
void list<T>::pop_front()
{
  if(!empty())
  {
    // Make the previous node the new head node
    pHead->pNext = pHead;
    numElements--;
  }

}

/*******************************************
 * list :: front
 *
 * Returns the element currently at the 
 * front of the list. This methods has
 * two versions, a setter and a getter.
 *
 * Parameters:
 *      none
 * Returns:
 *      nothing
 *******************************************/
template <class T>
T & list<T>::front()
{
  if(!empty())
  {
    return pHead->data;
  }
  else
  {
    throw "ERROR: unable to access data from an empty list";
  }
}
template <class T>
const T & list<T>::front() const
{
  if(!empty())
  {
    return pHead->data;
  }
  else
  {
    throw "ERROR: unable to access data from an empty list";
  }
}

/*******************************************
 * list :: back
 *
 * Returns the element currently at the 
 * back of the list. This methods has
 * two versions, a setter and a getter.
 *
 * Parameters:
 *      none
 * Returns:
 *      nothing
 *******************************************/
template <class T>
T & list<T>::back()
{
  if(!empty())
  {
    return pTail->data;
  }
  else
  {
    throw "ERROR: unable to access data from an empty list";
  }
}
template <class T>
const T & list<T>::back() const
{
  if(!empty())
  {
    return pTail->data;
  }
  else
  {
    throw "ERROR: unable to access data from an empty list";
  }
}

/*******************************************
 * list :: find
 *
 * Returns an iterator pointing to the
 * element being searched, if it is not 
 * found returns NULL
 *
 * Parameters:
 *      element: element to be searched
 *      in the list
 * Returns:
 *      pointer to location of the element
 *******************************************/
template <class T>
typename list<T>::iterator list<T>::find(const T &element)
{
  //  Go through the complete linked list to find value
  for (list<T>::iterator it = begin(); it != end(); it++)
  {
      // If value is in the list return pointer otherwise return NULL
    if (*it == element)
      return it;
  }
  return end();
}

/*******************************************
 * list :: insert
 *
 * Inserts an element in the middle of 
 * a list.
 *
 * Parameters:
 *      it: iterator to the element before
 *      which it will be inserted.
 *      element: the element to be entered
 * Returns:
 *      pointer to location of the new
 *      element
 * *******************************************/
template <class T>
typename list<T>::iterator list<T>::insert(iterator & it, const T & element)
{
      // New node created to be added to the linked list 
      Node * pNew = new Node(element);

      // If the list is empty, this first node is the head and tail
      if (numElements == 0)
      {
        pHead = pNew;
        pTail = pNew;
      }
      
      // If the node after is not null
      if (it.p)
      {
          // the next node of pNew will be the current node
          pNew->pNext = it.p;
          // the previous node of pNew will be the previous to the current node
          pNew->pPrev = it.p->pPrev;
          // the previous node of current will be pNew
          it.p->pPrev = pNew;

          // if there is a node before pNew set pNew as the next node for it
          if (pNew->pPrev)
            pNew->pPrev->pNext = pNew;

          // if iterator pointing to the head node, make the new node the head
          if (it.p == pHead)
            pHead = pNew;
      }
      // If it is, then we are making a new tail node
      else
      {
        pTail->pNext= pNew;
        pNew->pPrev = pTail;
        pTail = pNew;
      }
      
      numElements++;
      return iterator(pNew);
}

/*******************************************
 * list :: erase
 *
 * Removes an element from the middle of 
 * a list.
 *
 * Parameters:
 *      it: iterator to the element to be
 *      deleted
 * Returns:
 *      nothing
 * *******************************************/
template <class T>
void list<T>::erase(iterator & it)
{
  // if the pointer is not null proceed with deletion
  if(it.p != NULL)
  {
    // if there is a previous node
    if(it.p->pPrev)
    {
      // Point that previous node to the one after the iterator
      it.p->pPrev->pNext = it.p->pNext;
    }
    // otherwise, make the next node the new head node
    else
    {
      pHead = it.p->pNext;
      pHead->pPrev = NULL;
    }

    // if there is a node after
    if(it.p->pNext)
    {
      // Point that next node to the one before the iterator
      it.p->pNext->pPrev = it.p->pPrev;
    }
    // otherwise, make the previous node the new tail node
    else
    {
      pTail = it.p->pPrev;
      pTail->pNext = NULL;
    }

    // Decrease node count and delete node
    numElements--;
    delete it.p;
  }
  return;
}

/*******************************************
 * list :: assignment
 *
 * Assign a new list with the values from 
 * the rhs list.
 * Parameters:
 *      rhs: list to be used for assignment
 * Returns:
 *      list similar to rhs
 * *******************************************/
template <class T>
list<T> &list<T>::operator=(const list<T> &rhs)
{
  // If the list is empty, this first node is the head and tail
  if(rhs.size() == 0)
  {
    pHead = NULL;
    pTail = NULL;
    numElements = 0;
  }
  else
  { 
    // Copy the first node, its value and next node reference
    Node * currentNode = new Node(rhs.pHead->data);
    currentNode->pNext = rhs.pHead->pNext;
    // Set the first node as the head
    pHead = currentNode;
    numElements = 1;

    // If there is more than one node we need to copy the other nodes
    if(rhs.numElements > 1)
    {
      // go from the second node to the one before the last
      for (list<T>::iterator it = rhs.pHead->pNext; it != rhs.pTail; ++it)
      {
        // create new nodes, copy values and prev and next references
        Node * element = new Node(*it);
        currentNode->pNext = element;
        element->pPrev = currentNode;

        // update the current node with the lastest one created and 
        // increase the counter
        currentNode = element;
        numElements++;
      }

      // copy the last element of the list and make it the tail node
      Node * element = new Node(rhs.pTail->data);
      currentNode->pNext = element;
      element->pPrev = currentNode;
      pTail = element;
      numElements++;
    }
    // otherwise make this only node the tail node
    else
    {
      pTail = currentNode;
    }
    
    
  }
  return *this;
}


/*********************************************
  * List::Node class
  * 
  * Represents a node in a linked list
  *********************************************/
template <class T>
class list<T>::Node
{
public:
   // member variables
   T data;        // data to be stored on node of linked list  
   Node * pNext;  // Pointer to next node
   Node * pPrev;  // Pointer to previous node

   /***********************************************
    *   constructor and non-default constructor
    ***********************************************/

   // Default constructor: set all member variables to NULL
   Node() : pNext(NULL), pPrev(NULL), data(NULL) {};

   // Non-default constructor: assigns  data to element  
   Node(const T & element) {
      data = element;
      pNext = NULL;
      pPrev = NULL;
   }
}; // NODE

/*********************************************
  * List::iterator class
  * 
  * Class used to tranverse from through a list 
  * from the first to the last element while
  * allowing modification
  *********************************************/
template <class T>
class list<T>::iterator
{
public:
  // constructors, destructors, and assignment operator
  iterator() : p(NULL) {}
  iterator(Node *p) : p(p) {}
  iterator(const iterator &rhs) { *this = rhs; }
  iterator &operator=(const iterator &rhs)
  {
    this->p = rhs.p;
    return *this;
  }

  // equals, not equals operator
  bool operator!=(const iterator &rhs) const { return rhs.p != this->p; }
  bool operator==(const iterator &rhs) const { return rhs.p == this->p; }

  // dereference operator
  T &operator*() { return p->data; }
  const T &operator*() const { return p->data;}

  // prefix increment
  iterator &operator++()
  {
    p = p->pNext;
    return *this;
  }

  // prefix decrement
  iterator &operator--()
  {
    p = p->pPrev;
    return *this;
  }

  // postfix increment
  iterator operator++(int postfix)
  {
    iterator tmp(*this);
    p = p->pNext;
    return tmp;
  }

  // postfix decrement
  iterator operator--(int postfix)
  {
    iterator tmp(*this);
    p = p->pPrev;
    return tmp;
  }
  // Friend classes from list, to allow direct usage of private
  // variables of the iterator
  friend iterator list<T>::insert(iterator & it, const T & element);
  friend void list<T>::erase(iterator & it);
 
private:
  Node *p; // pointer to Node
};

/*********************************************
  * List::reverse_iterator class
  * 
  * Class used to tranverse from through a list 
  * from the last to the first element while
  * allowing modification
  *********************************************/
template <class T>
class list<T>::reverse_iterator
{
public:
  // constructors, destructors, and assignment operator
  reverse_iterator() : p(NULL) {}
  reverse_iterator(Node *p) : p(p) {}
  reverse_iterator(const reverse_iterator &rhs) { *this = rhs; }
  reverse_iterator &operator=(const reverse_iterator &rhs)
  {
    this->p = rhs.p;
    return *this;
  }

  // equals, not equals operator
  bool operator!=(const reverse_iterator &rhs) const { return rhs.p != this->p; }
  bool operator==(const reverse_iterator &rhs) const { return rhs.p == this->p; }

  // dereference operator
  T &operator*() { return p->data; }
  const T &operator*() const { return p->data;}

  // prefix increment
  reverse_iterator &operator++()
  {
    p = p->pPrev;
    return *this;
  }

  // prefix decrement
  reverse_iterator &operator--()
  {
    p = p->pNext;
    return *this;
  }

  // postfix increment
  reverse_iterator operator++(int postfix)
  {
    reverse_iterator tmp(*this);
    p = p->pPrev;
    return tmp;
  }

  // postfix decrement
  reverse_iterator operator--(int postfix)
  {
    reverse_iterator tmp(*this);
    p = p->pNext;
    return tmp;
  }
 
private:
  Node *p; // pointer to Node
};

/*********************************************
  * List::reverse_iterator class
  * 
  * Class used to tranverse from through a list 
  * from the first to the last element not
  * allowing modification
  *********************************************/
template <class T>
class list<T>::const_iterator
{
public:
  // constructors, destructors, and assignment operator
  const_iterator() : p(NULL) {}
  const_iterator(Node *p) : p(p) {}
  const_iterator(const iterator &rhs) { *this = rhs; }
  const_iterator &operator=(const const_iterator &rhs)
  {
    this->p = rhs.p;
    return *this;
  }

  // equals, not equals operator
  bool operator!=(const const_iterator &rhs) const { return rhs.p != this->p; }
  bool operator==(const const_iterator &rhs) const { return rhs.p == this->p; }

  // dereference operator
  T &operator*() { return p->data; }
  const T &operator*() const { return p->data;}

  // prefix increment
  const_iterator &operator++()
  {
    p = p->pNext;
    return *this;
  }

  // prefix decrement
  const_iterator &operator--()
  {
    p = p->pPrev;
    return *this;
  }

  // postfix increment
  const_iterator operator++(int postfix)
  {
    const_iterator tmp(*this);
    p = p->pNext;
    return tmp;
  }

  // postfix decrement
  const_iterator operator--(int postfix)
  {
    const_iterator tmp(*this);
    p = p->pPrev;
    return tmp;
  }

  // Friend classes from list, to allow direct usage of private
  // variables of the iterator
  friend const_iterator list<T>::insert(const_iterator & it, const T & element);
  friend void list<T>::erase(const_iterator & it);
 
private:
  Node *p; // pointer to Node
};

/*********************************************
  * List::reverse_iterator class
  * 
  * Class used to tranverse from through a list 
  * from the first to the last element not
  * allowing modification
  *********************************************/
template <class T>
class list<T>::const_reverse_iterator
{
public:
  // constructors, destructors, and assignment operator
  const_reverse_iterator() : p(NULL) {}
  const_reverse_iterator(Node *p) : p(p) {}
  const_reverse_iterator(const const_reverse_iterator &rhs) { *this = rhs; }
  const_reverse_iterator &operator=(const const_reverse_iterator &rhs)
  {
    this->p = rhs.p;
    return *this;
  }

  // equals, not equals operator
  bool operator!=(const const_reverse_iterator &rhs) const { return rhs.p != this->p; }
  bool operator==(const const_reverse_iterator &rhs) const { return rhs.p == this->p; }

  // dereference operator
  T &operator*() { return p->data; }
  const T &operator*() const { return p->data;}

  // prefix increment
  const_reverse_iterator &operator++()
  {
    p = p->pPrev;
    return *this;
  }

  // prefix decrement
  const_reverse_iterator &operator--()
  {
    p = p->pNext;
    return *this;
  }

  // postfix increment
  const_reverse_iterator operator++(int postfix)
  {
    const_reverse_iterator tmp(*this);
    p = p->pPrev;
    return tmp;
  }

  // postfix decrement
  const_reverse_iterator operator--(int postfix)
  {
    const_reverse_iterator tmp(*this);
    p = p->pNext;
    return tmp;
  }
 
private:
  Node *p; // pointer to Node
};
};
#endif