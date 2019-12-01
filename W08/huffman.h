/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H


#include <string>
#include "bnode.h"
#include "pair.h"
#include <list>

//Type definitions
typedef std::list<BNode<custom::pair<float, std::string> > *> huffmanList; //huffman list
typedef BNode<custom::pair<float, std::string> > huffmanNode; //Huffman BNode
typedef custom::pair<float, std::string> huffmanPair; // Huffman pair
typedef std::list<custom::pair<std::string, std::string> > PairStringList;// pair list

// receive the filename 
void huffman(const std::string & fileName);

/**************************************************
* Huffman class
*  Contains the method to creat a huffman tree
****************************************************/
class Huffman
{
  public:
	  //constructor and destructor
    Huffman(){}
    ~Huffman(){}

	//add elements to a node
    void addElements(const huffmanPair & rawData);
	//built a tree
    void build();

	//iterator of huffman list to find the node
    huffmanList::iterator getLocation(const huffmanNode * nodeToFind);
    
	//the huffmanList of the nodes
    huffmanList nodes;
};

#endif // HUFFMAN_h
