/***********************************************************************
* Header:
*    Node
* Summary:
*    This contains the prototypes and implementation of the node class.
*    The node class represents a member in a linked list. 
* Author
*    Jatsiri Detzani and Rolando Rodriguez
************************************************************************/
#include <cassert>  // for ASSERT
#include <iostream> // for CIN, COUT, ENDL

using std::cin;
using std::cout;
using std::endl;

#ifndef NODE_H
#define NODE_H

template <class T>

class Node
{
public:
   //member variables
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

/**************************************************
* copy()
* Copy a linked-list. Takes a pointer to a Node as a parameter
* and returns a newly created linked-list containing a copy of all the nodes
* within the list represented by the parameter.
* This is a non-member function.
****************************************************/
template <class T>
Node <T> * copy(const Node <T> * pSource) throw(const char*)
{
   // Initialize the destination linked list, where the new list will be copied
   Node <T> * pDestination = new Node<T>(pSource->data);

   // Pointer to first node of source linked list
   const Node <T> * pSrc = pSource;
   
   // Pointer to first node of destination linked list
   Node <T> * pDes = pDestination;

   // iterate through the source linked list to populate destination
   for (Node <T> * p = pSrc->pNext; p; p = p->pNext)
      pDes = insert(pDes, p->data, true);

   return pDestination;
}

/**************************************************
* insert()
* Insert a new node into the current linked-list. The first parameter is the
* reference Node next to which the new Node is inserted into the list.
* The second parameter is the value to be placed in the new Node, the third
* parameter called after is to determinate if the new node will be after or
* before the current node.
****************************************************/
template <class T>
Node <T> * insert( Node <T> * pCurrent,const T & element, bool after = false) throw(const char*)
{
   // New node created to be added to the linked list 
   Node <T> * pNew = new Node <T>(element);

   //insert before the current Node
   if (pCurrent != NULL && after == false)
   {
      // the next node of pNew will be the current node
      pNew->pNext = pCurrent;
      // the previous node of pNew will be the previous to the current node
      pNew->pPrev = pCurrent->pPrev;
      // the previous node of current will be pNew
      pCurrent->pPrev = pNew;

      // if there is a node before pNew set pNew as the next node for it
      if (pNew->pPrev)
         pNew->pPrev->pNext = pNew;
   }

   // insert after the current Node
   if (pCurrent != NULL && after == true)
   {
      //the previous node of pNew will be the current node
      pNew->pPrev = pCurrent;
      //the next node of pNew will be the next node of the current node
      pNew->pNext = pCurrent->pNext;
      //the next node of the current node is pNew
      pCurrent->pNext = pNew;

      // If there is a node after pNew make pNew the node before it
      if (pNew->pNext)
         pNew->pNext->pPrev = pNew;
   }

   //return the new node
   return pNew;
}

/******************************************************************************
* find()
* Find the Node corresponding to a given passed value from a given linked-list.
* The first parameter is a pointer to the front of the list, the second is the
* value to be found. The return value is a pointer to the found node if one
* exists.
******************************************************************************/
template <class T>
Node <T> * find(Node <T> * pHead, const T & element)
{
   //  Go through the complete linked list to find value 
   for (Node <T> * p = pHead; p; p = p->pNext)
   {
      // If value is in the list return pointer otherwise return NULL
      if (p->data == element)
         return p;
   }

   return NULL;
}

/**************************************************
* operator <<()
* Display the contents of a given linked-list.
****************************************************/
template <class T>
std::ostream & operator << (std::ostream & out, const Node <T> * pHead)
{
   // Go through the linked list
   for (const Node <T> * p = pHead; p; p = p->pNext)
   {
      // if the list got to its end do not print a comma for the last element
      if(p->pNext != NULL)
         out << p->data << ", ";
      else
         out << p->data;
   }
   return out;
}

/**************************************************
* freeData()
* Release all the memory contained in a given linked-list.
* The one parameter is a pointer to the head of list.
****************************************************/
template <class T>
void freeData(Node <T> * &pHead)
{
   // delete nodes until complete list disappears
   while (pHead != NULL)
   {
      Node <T> * pDelete = pHead;
      pHead = pHead->pNext;
      delete pDelete;
   }
}

/**************************************************
* remove()
* This will remove a given node from the linked list it is attached to.
* It takes a pointer to a Node as a parameter. this is the node to be
* deleted. It returns a pointer to the previous node in the list if such
* a node exists.
****************************************************/
template <class T>
Node <T> * remove(const Node <T> * pRemove)
{
   // Instantiate node to be returned after deletion
   Node <T> * pReturn;

   // If the node provided is null do nothing
   if (NULL == pRemove)
      return pReturn;
   // If there is a previous node fix reference to skip node to be deleted
   if (pRemove->pPrev)
      pRemove->pPrev->pNext = pRemove->pNext;
   // If there is a node after fix reference to skip node to be deleted
   if (pRemove->pNext)
      pRemove->pNext->pPrev = pRemove->pPrev;
   // If there is a previous node rerefence it, otherwise reference one after 
   if (pRemove->pPrev)
      pReturn = pRemove->pPrev;
   else
      pReturn = pRemove->pNext;
   // delete node, references have been removed, this node won't be accessed
   delete pRemove;

   return pReturn;
}

#endif
