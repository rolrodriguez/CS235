/***********************************************************
* Header:
*   Binary Node.
* Sumary:
*   This contains the prototypes and implementation of the binary node class. 
*  Author
*    Jatsiri Detzani and Rolando Rodriguez
**************************************************************/
#include <cassert>  // for ASSERT
#include <iostream> // for CIN, COUT, ENDL

using std::cin;
using std::cout;
using std::endl;

#ifndef BNODE_H
#define BNODE_H

template <class T>

class BNode
{
public:
	//member variables
	T data;        // data to be stored on binary node  
	BNode * pLeft;  // Pointer to left childnode
	BNode * pRight;  // Pointer to right child node
	BNode * pParent; // Pointer to parent node

	/***********************************************
	 *   constructor and non-default constructor
	 ***********************************************/

	 // Default constructor: set all member variables to NULL
	BNode() : pLeft(NULL), pRight(NULL), pParent(NULL){};

	// Non-default constructor: assigns  data to element  
	BNode(const T & element) {
		data = element;
		pLeft = NULL;
		pRight = NULL;
		pParent = NULL;
	}
}; // BNODE

/*******************************************************************
*addLeft():
* Adds a node to the left of the current node. 
* There are two versions of this method: one that takes a template variable as a parameter, 
* and one that takes a BNode * as a parameter. In the former case, a new node will be allocated. 
* In the later case, the passed node will be used. In both cases, pLeft of the current node will 
* point to the new node, and pParent of the new node will point to the current node. The return value is void.
* In the case of an allocation error, the following c-string exception will be thrown:
* ERROR: Unable to allocate a node
*
*********************************************************************/
template <class T>
void addLeft(BNode <T> * pNode, BNode <T> * pAdd)
{
	if (pAdd != NULL)
		pAdd->pParent = pNode; // parent point to the current node
	pNode->pLeft = pAdd; // pLeft of the current node pointing to pAdd node

}

template <class T>
void addLeft(BNode <T> * pNode, const T & t) throw(const char *)
{
	BNode <T> * pAdd = new BNode <T>(t); //allocate a new node
	pAdd->pParent = pNode; // parent point to the current node
	pNode->pLeft = pAdd; // pLeft of the current node pointing to the new node

}
/*******************************************************************
*addRight()
* Exactly the same as addLeft() except on the right side.
*
*********************************************************************/
template <class T>
void addRight(BNode <T> * pNode, BNode <T> * pAdd)
{
	if (pAdd != NULL)
		pAdd->pParent = pNode; // parent point to the current node
	pNode->pRight = pAdd; // pRight of the current node pointing to pAdd node


}

template <class T>
void addRight(BNode <T> * pNode, const T & t) throw(const char*)
{
	BNode <T> * pAdd = new BNode <T> (t); //allocate a new node
	pAdd->pParent = pNode; // parent point to the current node
	pNode->pRight = pAdd; // pRight of the current node pointing to the new node

}

/*******************************************************************
*sizeBTree()
* Takes a BNode pointer as a parameter and returns the number of nodes
* under that node (including itself). This is a recursive function.
*
*********************************************************************/
template <class T>
int sizeBTree(const BNode <T> * pRoot)
{
	if (pRoot == NULL)
		return 0;
	else
		//The size of the sub-tree under pRoot is the same as the size of the sub-tree under
		// pLeft plus the size of the sub-tree under pRight plus one
		return sizeBTree(pRoot->pLeft) + 1 + sizeBTree(pRoot->pRight);

}

/*******************************************************************
*deleteBTree()
* Takes a BNode as a parameter and deletes all the children and itself. 
* This is a recursive function.
*********************************************************************/
template <class T>
void deleteBTree(BNode <T> * &pNode)
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

/*******************************************************************
*copyBTree()
*  Takes a BNode as a parameter makes a copy of the tree.
* The return value is the newly copied tree. This is a recursive function.
*********************************************************************/
template <class T>
BNode <T> * copyBTree(const BNode <T> * pSrc) throw(const char *)
{
	if (pSrc == NULL)
		return NULL;

   BNode <T> * destination = new BNode <T> (pSrc->data); // alocate a new node

   // copy the left sub-trees
	destination->pLeft = copyBTree(pSrc->pLeft);
	if (destination->pLeft != NULL)
		destination->pLeft->pParent = destination;

	//copy the right sub-trees
	destination->pRight = copyBTree(pSrc->pRight);
	if (destination->pRight != NULL)
		destination->pRight->pParent = destination;

	//return the copy node
	return destination;
}

/*******************************************************************
*Insertion Operator <<
* Takes an ostream and a constant BNode * as a parameter and displays
* the tree under the passed parameter. Don't forget to return the ostream 
* as all insertion operators should do. This is a recursive function traversing
* the tree in LVR order. A single space will be displayed after every element.
*********************************************************************/
template <class T>
std::ostream & operator << (std::ostream & out, BNode <T> * pNode)
{ 
	if (pNode != NULL) //Check if the underlying node is not NULL.
	{
		cout << pNode-> pLeft; // go to the left sub-tree
		out << pNode-> data << " "; //visit the underlying node
		cout << pNode-> pRight; // go to the right sub.tree
	}
	return out;
}
#endif
