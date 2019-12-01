/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother Kirby, CS 235
 * Author:
 *    Jatsiri Detzani & Rolando Rodriguez
 * Summary:
 *    Create a binary search tree
 ************************************************************************/
#include <cassert>
#include <iostream>

#ifndef BST_H
#define BST_H

namespace custom
{
/*********************************************
* BST class - Binary Search Tree structure
* 
* Collection of items implemented using
* Binary tree nodes.
 *********************************************/
template <class T>
class BST
{
public:
  /****************************************** 
   *       constructors and destructors
   *******************************************/

	// Default constructor
	BST() : root(NULL), numElements(0) {}

	// Copy constructor: creates a BST with the same content as rhs
	BST(const BST<T> &rhs)
	throw(const char *);

	// Destructor: deletes all trees
	~BST() { clear(); }

	/******************************************* 
         *   standard container interfaces
         *******************************************/

	// boolean that shows if the BST is empty
	bool empty() { return numElements == 0; }

	// shows how many nodes are in the BST
	int size() { return numElements; }

	// Eliminates all elements from container
	void clear();

	/********************************************** 
         * BST nested classes and iterators classes
         **********************************************/

	// Iterator nested class
	class iterator;

	// Reverse iterator nested class
	class reverse_iterator;

	// Binary Node nested class
	class BNode;

	/******************************************* 
         *        specific list interfaces
         *******************************************/

	// Add an element to the tree
	void insert(const T &t) throw(const char *);

	// Reference to root node
	BNode *getRoot() { return root; }

	// Deletes and element in tree given an iterator to it
	void erase(iterator &it);

	// Returns an iterator with the position of an element in the tree
	iterator find(const T &t);

	/********************************************** 
        *   iterators to the start and end of BST
        **********************************************/

	iterator begin();
	iterator end() { return iterator(NULL); }
	iterator rbegin();
	iterator rend() { return iterator(NULL); }

	/********************************************** 
        *          operator overloading
        **********************************************/

	//	Assignment operator
	BST<T> &operator=(const BST &rhs) throw(const char *);

	// Insertion operator for BST
	friend std::ostream &operator<<(std::ostream &out, BST<T> &tree)
	{
		out << "{  ";
		if (tree.root != NULL) //Check if the underlying node is not NULL.
		{
			out << tree.root;
		}
		out << "}";
		return out;
	}

	// Insertion operator for BNode
	friend std::ostream &operator<<(std::ostream &out, BNode *pNode)
	{
		if (pNode != NULL) //Check if the underlying node is not NULL.
		{

			out << pNode->pLeft;// go to the left sub-tree
			out << pNode->data << "  "; //visit the underlying node
			out << pNode->pRight;				// go to the right sub.tree
		}
		return out;
	}

private:
	// Pointer to root binary node
	BNode *root;

	// Number of elements in the tree
	int numElements;

	// Method to delete a node
	void deleteNode(BNode *pNode, bool right);

	// Method to delete a binary tree (parent and children)
	void deleteBTree(BNode *pNode);

	// Method to copy a binary tree
	BNode *copyBTree(BNode *src)
	{
		if (src == NULL)
			return NULL;

		BNode *dest = new BNode(src->data); // alocate a new node

		// copy the left sub-trees
		dest->pLeft = copyBTree(src->pLeft);
		if (dest->pLeft != NULL)
			dest->pLeft->pParent = dest;

		//copy the right sub-trees
		dest->pRight = copyBTree(src->pRight);
		if (dest->pRight != NULL)
			dest->pRight->pParent = dest;

		//return the copy node
		return dest;
	}
}; // BST class

/*******************************************
 * BST :: clear
 *
 * Deletes all trees from the BST
 *
 * Parameters:
 *      none
 * Returns:
 *     nothing
 *******************************************/
template <class T>
void BST<T>::clear()
{
	// Delete if there are elements
	if (numElements > 0)
	{
		deleteBTree(root);
		root = NULL;
	}
	numElements = 0; //set numElements to cero
}

/*******************************************
 * BST :: COPY CONSTRUCTOR
 *
 * Creates a copy of the rhs BST
 *
 * Parameters:
 *      rhs: constant BST to make the copy
 *      from.
 *******************************************/
template <class T>
BST<T>::BST(const BST<T> &rhs) throw(const char *)
{
	try
	{
		this->root = copyBTree(rhs.root); // copy root
		this->numElements = rhs.numElements; //copy num elements
	}
	catch (std::bad_alloc) // throw an error if the allocation fails
	{
		throw "ERROR: Unable to allocate a node";
	}
}

/*******************************************
 * BST :: begin
 *
 * Provides an iterator to the beginning
 * of the BST
 *
 * Parameters:
 *      none
 * Returns:
 *    iterator to the first node of the
 *      binary tree
 *******************************************/
template <class T>
typename BST<T>::iterator BST<T>::begin()
{
	if (root != NULL)
	{

		BNode *leftNode = root; //create a node

		while (leftNode->pLeft) //while left node is not null
		{
			leftNode = leftNode->pLeft; // left node is equal to the its left node
		}

		return iterator(leftNode); //iterator to the first node of the binary tree
	}
	else
		return iterator(); //return iterator
}

/*******************************************
 * BST :: rbegin
 *
 * Provides an iterator to the reverse beginning
 * of the BST
 *
 * Parameters:
 *      none
 * Returns:
 * 	iterator referring to the rightmost 
 *      element in the BST.
 *******************************************/
template <class T>
typename BST<T>::iterator BST<T>::rbegin()
{
	if (root != NULL)
	{

		BNode *rightNode = root; //create a node

		while (rightNode->pRight) //while the right node is not null
		{
			rightNode = rightNode->pRight; // right node is equal to its right child
		}

		return iterator(rightNode); //return the iterator referring to the rightmost 

	}
	else
		return iterator(); //return iterator
}

/*******************************************
 *  INSERT()
 *******************************************/
template <class T>
void BST<T>::insert(const T &t) throw(const char *)
{
   try
   {
      BNode *newNode = new BNode(t); // allocate newNode
      if (numElements == 0) // if there is not elements
      {
         root = newNode; // assign newNode to root node
         numElements++; //increase numElements by one
         return;
      }
      else
      {
         BNode *pNext = root;// create a new node
         while (pNext)
         {
            if (t < pNext->data) //if t element is less or equal to pNext data
            {
               if (pNext->pLeft == NULL) // if left child is null
               {
                  pNext->pLeft = newNode; //left child is equal to newNode
                  newNode->pParent = pNext; // parent is equal to pNext node
                  pNext = NULL; //set pNext to null
               }
               else
                  pNext = pNext->pLeft; //pNext is equal to the left child
            }
            else
            {
               if (pNext->pRight == NULL) //if the right child is null
               {
                  pNext->pRight = newNode; // assign newNode to right child of pNext
                  newNode->pParent = pNext; // parent is equal to pNext node
                  pNext = NULL; //set pNext to null
               }
               else
                  pNext = pNext->pRight; //pNext is equal to the right child
            }
         }
      }

      numElements++; //increment numElements by one
   }
   catch (const std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/*******************************************
 * BST :: FIND
 *******************************************/
template <class T>
typename BST<T>::iterator BST<T>::find(const T &t)
{
	iterator it = iterator(this->root);

	while (*it > t) //if it is less than t element
	{
		it--; // decrease it
	}

	while (*it < t) // if it is less  than t element
	{
		it++; // increase it
	}

	if (*it == t) // if it is equal to t element return it
		return it;

	return end(); // else return ent()
}

template <class T>

/************************************************************
* erase()
* Parameter:
*  The parameter is an iterator referring to the element
*   to be removed from the binary search tree. The node
*   will then be removed following the algorithm presented in the textbook. 
*Return value:
*    There is no return value.
**************************************************************/
void BST<T>::erase(iterator &it)
{

   // No children case
   if (it.p->pRight == NULL && it.p->pLeft == NULL)
   {
      if (it.p->pParent != NULL && it.p->pParent->pRight == it.p) //if parent exist and the right child is equat to it
         it.p->pParent->pRight = NULL; //set the right child to null
      if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)//if parent exist and the left child is equat to it
         it.p->pParent->pLeft = NULL; //set the left child to null
      deleteNode(it.p, false); //delete it
      return;
   }
	// One child case
   if (it.p->pRight == NULL && it.p->pLeft != NULL) // if the left child exists and right child doesn't exist
   {
      it.p->pLeft->pParent = it.p->pParent; // set the it's parent to left child's parent
      if (it.p->pParent != NULL && it.p->pParent->pRight == it.p) //if parent exists and the right child is equat to it
         it.p->pParent->pRight = it.p->pLeft; // set the right child of it's parent  to left child of it
      if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)//if parent exists and the left child is equat to it
         it.p->pParent->pLeft = it.p->pLeft;// set the left child of it's parent  to left child of it
      deleteNode(it.p, false); // delete it
      return;
   }
   if (it.p->pLeft == NULL && it.p->pRight != NULL) // if the right child exists and left child doesn't exist
   {
      it.p->pRight->pParent = it.p->pParent;  // set the it's parent to right child's parent
      if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)  //if parent exists and the right child is equat to it
         it.p->pParent->pRight = it.p->pRight;  // set the right child of it's parent  to right child of it
      if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)//if parent exists and the left child is equat to it
         it.p->pParent->pLeft = it.p->pRight; // set the left child of it's parent  to right child of it
      deleteNode(it.p, true); //delete it
      return;
   }
	// Two children case
   else if (it.p->pLeft != NULL && it.p->pRight != NULL) // two childs exist
   {
      BNode *successor = it.p; //new node is equal to it.p node
      if (successor->pRight != NULL) // if right child of successor exists
      {
         successor = successor->pRight; // successor is equal to the right child of successor
         while (successor->pLeft != NULL) // while left child exists
         {
            successor = successor->pLeft;  // successor is equal to its left child node
         }
         it.p->data = successor->data; // it.p's data is equal to successor's data
         successor->pParent->pLeft = NULL; // set left child to null
         if (successor->pRight != NULL) // if successor's right child
         {
            successor->pRight->pParent = successor->pParent; // the parent of right child is the parent of succesor
            successor->pParent->pLeft = successor->pRight; // the parent of left child is the right child
            successor->pRight = NULL; //set right child to null
         }

         delete successor; //delete successor
         successor = NULL; //set successor to null
      }
   }

   return;
}

/*******************************************
 *  ASSIGN OPERATOR
 *  Copy one binary search tree onto another.
 *******************************************/
template <class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) throw(const char *)
{
	this->root = this->copyBTree(rhs.root); // copy root
	this->numElements = rhs.numElements; // copy numElements

	return *this; // return the copy
}
/*******************************************
 *  Class BNode
 *******************************************/
template <class T>
class BST<T>::BNode
{
public:
	//member variables
	T data;	// data to be stored on binary node
	BNode *pLeft;	// Pointer to left childnode
	BNode *pRight;	// Pointer to right child node
	BNode *pParent; // Pointer to parent node
	bool isRed;
	/***********************************************
	 *   constructor and non-default constructor
	 ***********************************************/

	// Default constructor: set all member variables to NULL
	BNode() : pLeft(NULL), pRight(NULL), pParent(NULL){};

	// Non-default constructor: assigns  data to element
	BNode(const T &element)
	{
		data = element;
		pLeft = NULL;
		pRight = NULL;
		pParent = NULL;
	}
}; // BNODE
/***********************************************
* deleteBTree()
* Takes a BNode as a parameter and deletes all the children and itself.
* This is a recursive function.
*********************************************************************/
template <class T>
void BST<T>::deleteBTree(BNode *pNode)
{
	if (pNode == NULL)
		return;

	//delete all the children
	deleteBTree(pNode->pLeft);
	deleteBTree(pNode->pRight);
	//delete itself
	delete pNode;

	pNode = NULL;
}


/***********************************************
* deleteNode()
************************************************/
template <class T>
void BST<T>::deleteNode(BNode *pNode, bool right)
{
   BNode *pNext = (right ? pNode->pRight : pNode->pLeft);// create a node, if right is true, pNext is equal to pNode's right child, else is equal to pNode's left child

   if (pNode != root) // if pNode is not equal to root
   {
      if (pNode->pParent->pLeft == pNode) //if  the parent of left child is equal to pNode
      {
         pNode->pParent->pLeft = pNext; // the left child's parent is equl to pNext
      }
      else
      {
         pNode->pParent->pRight = pNext; // the right child's parent is equl to pNext
      }
   }
   else
   {
      root = pNext; // root node is equal to pNext
      pNext->pParent = NULL; //the pNext parent is set to null
   }
   delete pNode; // delete pNode
}

/*********************************************
  * List::iterator class
  *
  * Class used to tranverse from through a list
  * from the first to the last element while
  * allowing modification
  *********************************************/
template <class T>
class BST<T>::iterator
{
public:
	// constructors, destructors, and assignment operator
	iterator() : p(NULL) {}
	iterator(BNode *p) : p(p) {}
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
	const T &operator*() const { return p->data; }

	// prefix increment
	iterator &operator++();

	// prefix decrement
	iterator &operator--();

	// postfix increment
	iterator operator++(int postfix)
	{
		iterator tmp = *this;
		++(*this);
		return tmp;
	}

	// postfix decrement
	iterator operator--(int postfix)
	{
		iterator tmp = *this;
		--(*this);
		return tmp;
	}
	// Friend classes from list, to allow direct usage of private
	// variables of the iterator
	// friend iterator BST<T>::insert(iterator & it, const T & element);
	friend void BST<T>::erase(iterator &it);

private:
	BNode *p; // pointer to Node
};

/*********************************************
  * List::reverse_iterator class
  *
  * Class used to tranverse from through a list
  * from the last to the first element while
  * allowing modification
  *********************************************/
template <class T>
class BST<T>::reverse_iterator
{
public:
	// constructors, destructors, and assignment operator
	reverse_iterator() : p(NULL) {}
	reverse_iterator(BST<T>::BNode *p) : p(p) {}
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
	const T &operator*() const { return p->data; }

	// prefix increment
	reverse_iterator &operator++()
	{
		--p;
		return *this;
	}

	// prefix decrement
	reverse_iterator &operator--()
	{
		++p;
		return *this;
	}

	// postfix increment
	reverse_iterator operator++(int postfix)
	{
		reverse_iterator tmp = *this;
		--p;
		return tmp;
	}

	// postfix decrement
	reverse_iterator operator--(int postfix)
	{
		reverse_iterator tmp = *this;
		++p;
		return tmp;
	}

private:
	BNode *p; // pointer to Node
};

/**************************************************
 * BST ITERATOR :: increment PREFIX
 *
 *************************************************/
template <class T>
typename BST<T>::iterator &BST<T>::iterator ::operator++()
{
	// do nothing if we have nothing
	if (NULL == p)
		return *this;

	// if there is a left node, take it
	if (NULL != p->pRight)
	{
		// go right
		p = p->pRight;

		// jig left - there might be more right-most children
		while (p->pLeft)
			p = p->pLeft;
		return *this;
	}

	// there are no left children, the right are done
	assert(NULL == p->pRight);
	BNode *pSave = p;

	// go up
	p = p->pParent;

	// if the parent is the NULL, we are done!
	if (NULL == p)
		return *this;

	// if we are the right-child, got to the parent.
	if (pSave == p->pLeft)
		return *this;

	// we are the left-child, go up as long as we are the left child!
	while (NULL != p && pSave == p->pRight)
	{
		pSave = p;
		p = p->pParent;
	}

	return *this;
}
/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one.
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
typename BST<T>::iterator &BST<T>::iterator ::operator--()
{
	// do nothing if we have nothing
	if (NULL == p)
		return *this;

	// if there is a left node, take it
	if (NULL != p->pLeft)
	{
		// go left
		p = p->pLeft;

		// jig right - there might be more right-most children
		while (p->pRight)
			p = p->pRight;
		return *this;
	}

	// there are no left children, the right are done
	assert(NULL == p->pLeft);
	BNode *pSave = p;

	// go up
	p = p->pParent;

	// if the parent is the NULL, we are done!
	if (NULL == p)
		return *this;

	// if we are the right-child, got to the parent.
	if (pSave == p->pRight)
		return *this;

	// we are the left-child, go up as long as we are the left child!
	while (NULL != p && pSave == p->pLeft)
	{
		pSave = p;
		p = p->pParent;
	}

	return *this;
}

} // namespace custom

#endif // BST_H
