/***********************************************************************
 * Component:
 *    Assignment 10, Maps
 *    Brother Kirby, CS 235
 * Author:
 *    Jatsiri Detzani & Rolando Rodriguez
 * Summary:
 *    Create a map using a BST
 ************************************************************************/

#include <iostream>
#include "bst.h"
#include "pair.h"

#ifndef MAP_H
#define MAP_H

/*********************************************
 * Map class - Map structure
 * 
 * Pair of values implemented using Binary
 * Search trees.
 *********************************************/
namespace custom
{
template <class Key, class Value>
class map
{
private:
	BST<pair<Key, Value> > bst; // BST to hold the pair of values that make the map

public:
	/****************************************** 
   *       constructors and destructors
   ******************************************/

	// Default constructor: creates an empty map
	map() {}

	// Copy constructor: creates a new map with the same content
	map(const map<Key, Value> &rhs)
	{
		try
		{
			this->bst = rhs.bst; // copy bst
		}
		catch (std::bad_alloc) // throw an error if the allocation fails
		{
			throw "ERROR: Unable to allocate a node";
		}
	}

	// Destructor: deletes all nodes from the BST
	~map() { clear(); }

	/******************************************* 
   *   standard container interfaces
   *******************************************/
	
	// shows how many nodes are in the BST
	int size() { return bst.size(); }
	
	// boolean that indicates if the map is empty
	bool empty() { return bst.empty(); }

	// Eliminates all elements from container
	void clear() { bst.clear(); }

	/********************************************** 
   *          operator overloading
   **********************************************/

	// Assignment
	map<Key, Value> &operator=(const map<Key, Value> &rhs)
	{
		this->bst = rhs.bst;
		return *this;
	}

	// Access
	Value &operator[](const Key &key);
	const Value operator[](const Key & key) const;

	// Insertion
	friend std::ostream &operator<<(std::ostream &out, map<Key, Value> &mMap)
	{
		//out << mMap.bst;
		typename BST<pair <Key, Value> >::iterator it;
		out << "{  ";
		for(it = mMap.bst.begin();it != mMap.bst.end();++it)
		{
			out << (*it).getSecond() << "  ";
		}
		out << "}";
		return out;
	}

	//map iterator
	class iterator;
	class reverse_iterator;

	/******************************************* 
   *        specific list interfaces
   *******************************************/

	 // Find method: to locate items in the collection
	iterator find(const Key &key)
	{
		pair<Key, Value> newPair(key, Value());
		typename BST<pair<Key, Value> >:: iterator it = bst.find(newPair);
		iterator it1=it;
		return it1;
	}

		//insert functions
	void insert(const pair<Key, Value> &input);
	void insert(const Key &key, const Value &value);


	/********************************************** 
   *   iterators to the start and end of map
   **********************************************/

	/*******************************************
	 * map :: begin
	 *
	 * Provides an iterator to the beginning
	 * of the map
	 *
	 * Parameters:
	 *      none
	 * Returns:
	 *    iterator to the first node of the
	 *    map
	 *******************************************/
	iterator begin() 
	{ 
		pair<Key, Value> newPair(Key, Value);
		typename BST<pair<Key, Value> >::iterator it = bst.begin();
		iterator it1(it);
		return it1;
	}

	/*******************************************
	 * map :: end
	 *
	 * Provides an iterator past the last 
	 * element of the map
	 *
	 * Parameters:
	 *      none
	 * Returns:
	 *    iterator past element of the
	 *    map
	 *******************************************/
	iterator end() 
	{ 
		pair<Key, Value> newPair(Key, Value);
		typename BST<pair<Key, Value> >::iterator it = bst.end();
		iterator it1(it);
		return it1;
	}

	/*******************************************
	 * map :: rbegin
	 *
	 * Provides a reverse iterator to the end of
	 * of the map
	 *
	 * Parameters:
	 *      none
	 * Returns:
	 *    iterator to the last node of the
	 *    map
	 *******************************************/
	reverse_iterator rbegin()
	{ 
		pair<Key, Value> newPair(Key, Value);
		typename BST<pair<Key, Value> >::reverse_iterator it = bst.rbegin();
		reverse_iterator it1(it);
		return it1;
	}

	/*******************************************
	 * map :: rend
	 *
	 * Provides a reverse iterator to the 
	 * beginning of the map
	 *
	 * Parameters:
	 *      none
	 * Returns:
	 *    iterator to before the first node of
	 *    the map
	 *******************************************/
	reverse_iterator rend()
	{
		pair<Key, Value> newPair(Key, Value);
		typename BST<pair<Key, Value> >::reverse_iterator it = bst.rend();
		reverse_iterator it1(it);
		return it1;
	}

}; //end map

/***********************************************************
	* map::insert
	*
	* Add an element to the collection to the right position
	* to follow the rules of a BST.
	*	
	*	Parameters:
	*			1) input at a Key, Value pair (or)
	*			2) key and value as separate values
	* Returns:
	*			Nothing
	**********************************************************/
template <class Key, class Value>
void map<Key, Value>::insert(const pair<Key, Value> &input)
{
	typename BST<pair<Key, Value> >::iterator it = bst.find(input);
	if (it != NULL)
		*it = input;
	else
		bst.insert(input);
}

template <class Key, class Value>
void map<Key, Value>::insert(const Key &key, const Value &value)
{
	pair<Key, Value> newPair(key, value);

	bst.insert(newPair);
}
/***********************************************************
 * map:: access operator []
 * 
 * Provides access to elements from the map given the key.
 * 
 * Parameters:
 * 			Key or identifier to retrieve the data with
 * Returns:
 * 			Value related to key provided
 *
 **********************************************************/
template <class Key, class Value>
Value &map<Key, Value>::operator[](const Key &key)
{
	pair<Key, Value> newPair(key, Value());
	typename BST<pair<Key, Value> >::iterator it = bst.find(newPair);

	if (it != NULL)
	{
		return (*it).second;
	}
	else
	{
		bst.insert(newPair);
		return (*bst.find(newPair)).second;
	}
}
template <class Key, class Value>
const Value map<Key, Value>::operator[](const Key &key) const
{
	pair<Key, Value> newPair(key, Value());
	typename BST<pair<Key, Value> >::iterator it = bst.find(newPair);

	if (it != NULL)
	{
		return (*it).second;
	}
	else
	{
		bst.insert(newPair);
		return (*bst.find(newPair)).second;
	}
}

/*********************************************
  * map::iterator class
  *
  * Class used to tranverse from through a map
  * from the first to the last element while
  * allowing modification
  *********************************************/
template <class Key, class Value>
class map<Key, Value>::iterator
{
public:
	// constructors, destructors, and assignment operator
	iterator() : it(NULL) { }
	iterator(typename BST<pair<Key, Value> >::iterator itBST): it(itBST){}
	iterator(const iterator &rhs) 
	{ 
		*this = rhs; 
	}
	iterator &operator=(const iterator &rhs)
	{
		this->it = rhs.it;
		return *this;
	}

	// equals, not equals operator
	bool operator!=(const iterator &rhs) const { return rhs.it != this->it; }
	bool operator==(const iterator &rhs) const { return rhs.it == this->it; }

	// dereference operator
	pair<Key,Value> &operator*() { return (*it); }
	const pair <Key, Value> &operator*() const { return (*it); }

	// prefix increment
	iterator &operator++()
	{
		++it;
		return *this;
	}

	// prefix decrement
	iterator &operator--()
	{
		--it;
		return *this;
	}

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
private:
	typename BST<pair<Key, Value> >::iterator it; // BST
};

/*********************************************
  * map::reverse_iterator class
  *
  * Class used to tranverse from through a map
  * from the last to the first element while
  * allowing modification
  *********************************************/
template <class Key, class Value>
class map<Key, Value>::reverse_iterator
{
public:
	// constructors, destructors, and assignment operator
	reverse_iterator() : it(NULL) {}
	reverse_iterator(typename BST<pair<Key,Value> >::reverse_iterator itBST):it(itBST){}
	reverse_iterator(const reverse_iterator &rhs)
	{ 
		*this = rhs;
	}
	reverse_iterator &operator=(const reverse_iterator &rhs)
	{
		this->it = rhs.it;
		return *this;
	}

	// equals, not equals operator
	bool operator!=(const reverse_iterator &rhs) const { return rhs.it != this->it; }
	bool operator==(const reverse_iterator &rhs) const { return rhs.it == this->it; }

	// dereference operator
	Value &operator*() { return (*it); }
	const Value &operator*() const { return (*it); }

	// prefix increment
	reverse_iterator &operator++()
	{
		--it;
		return *this;
	}

	// prefix decrement
	reverse_iterator &operator--()
	{
		++it;
		return *this;
	}

	// postfix increment
	reverse_iterator operator++(int postfix)
	{
		reverse_iterator tmp = *this;
		--it;
		return tmp;
	}

	// postfix decrement
	reverse_iterator operator--(int postfix)
	{
		reverse_iterator tmp = *this;
		++it;
		return tmp;
	}

private:
	typename BST<pair<Key, Value> >::iterator it; // pointer to Node
};

} // namespace custom

#endif
