/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Jatsiri Detzani and Rolando Rodriguez
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/
#include <iostream> // for CIN and COUT
#include <fstream>	// for IFSTREAM
#include <cassert>	// for ASSERT
#include <string>		// for STRING: binary representation of codes
#include "huffman.h" // for HUFFMAN() prototype


using std::bad_alloc;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

/************************************************************
* getHuffmanCode()
*  Find the path to every leaf node in the tree
*	parameters:
*			-node: node in tree to get the code for
*			-text: starting string to add the index to.
*			-relations: pair of strings keeping the ID and 
*			code for each entry
* returns:
*			-nothing
**************************************************************/
void getHuffmanCode(const huffmanNode * node, std::string text, PairStringList & relations)
{
	// if these are leaf nodes
	if(node->pLeft == NULL && node->pRight == NULL)
	{
		// create a pair with the string and float values with the tree data
		custom::pair<std::string, std::string> results(node->data.getSecond(), text);
		// add the pair of strings with the content to the list
		relations.push_back(results);

	}
	// otherwise is another type of node
	else
	{
		//assign 0 to left elements
		getHuffmanCode(node->pLeft, text + "0", relations);
		//assign 1 to right elements
		getHuffmanCode(node->pRight, text + "1", relations);
	}
	
}
/***************************************************
* Operator <<
* output the elements of the tree
* 	parameters:
*				-out: ouput stream to use
*				-rhs: huffman tree instance to print
*		returns:
*				-output stream containing the output
****************************************************/
std::ostream & operator << (std::ostream & out, Huffman & rhs)
{
	//iterate through the complete tree to print contents
	out << "{";
	for (huffmanList::iterator it = rhs.nodes.begin(); it != rhs.nodes.end();++it)
	{
		out << *it;
	}
	out << "}";
	return out;
}

/**************************************************
* getLocation() iterator
* Find the iterator for the place before the node
*
*		-Parameters:
*				-nodeToFind: nodeto get the location for
*		-Returns:
*				-iterator to the node found
***************************************************/
huffmanList::iterator Huffman::getLocation(const huffmanNode * nodeToFind)
{
	//iterate the huffman list
	for (huffmanList::iterator it = nodes.begin(); it != nodes.end();++it)
	{
		if ((*it)->data > nodeToFind->data)
			return it;
	}
	return nodes.end();
}

/**************************************************************
*addElements()
* Add elements to huffmanNode
*		Parameters:
*					-rawData: pair including data to be included into
*					the huffman tree
*		Returns:
*					-nothing
****************************************************************/
void Huffman::addElements(const huffmanPair & rawData)
{
	//allocate a new huffmanNode
	huffmanNode * newRawData = new huffmanNode(rawData);

	//check if is empty
	if(nodes.empty())
	{
		//push newRawData to front of nodes
		nodes.push_front(newRawData);
	}

	else if (nodes.front()->data > newRawData->data)
	{
		//push newRawData to front of nodes
		nodes.push_front(newRawData);
	}
	else
	{
		//find the location of newRawData and assign it to it
		huffmanList::iterator it = getLocation(newRawData);

		//if this is no pointing to the end
		if (it != nodes.end())
		{
			//called insert function and pass it and newRawData 
			nodes.insert(it, newRawData);
		}
		else
		{
			//push newRawData to back of nodes
			nodes.push_back(newRawData);
		}
		
	}
	
}
/*******************************************************
*build()
* Takes the list and built one tree with sub-trees
*
********************************************************/
void Huffman::build()
{
	// if the tree has only one or less items skip it 
	if (nodes.size() <= 1)
	{
		return;
	}

	huffmanNode *newRawData = new huffmanNode; //allocate a new huffmanNode
	huffmanList::iterator it = nodes.begin();  //point to the start of the list

	float total = (*it)->data.getFirst(); //assign the first to total
	newRawData->pLeft = *it; // nake the element the child to the left side
	(*it)->pParent = newRawData; // make the new node the parent of it
	
	nodes.pop_front(); // remove the first element from the node list

	it = nodes.begin(); // Go back to the first position
	total += (*it)->data.getFirst(); //add the first element of it to total
	newRawData->data.first = total; //assign total to the first element of newRawData
	newRawData->pRight = *it; //assign it to the right child of newRawData
	(*it)->pParent = newRawData; //assign newRawData as parent node of it

	nodes.pop_front(); // remove the first element from the node list

	it = nodes.begin(); 
	if(*it == NULL)				// if the list of nodes is empty
	{
		nodes.push_front(newRawData); //push newRawData to front of nodes
		return;
	}
	if ((*it)->data.getFirst() > newRawData->data.getFirst())
	{
		nodes.push_front(newRawData); //push newRawData to front of nodes
	}
	else
	{
		//find the location of newRawData and assign it to it
		huffmanList::iterator it = getLocation(newRawData);

		if (it != nodes.end()) //if it is different of end of nodes
			nodes.insert(it, newRawData); //call the function insert and pass it and newRawData
		else
			nodes.push_back(newRawData); //othersie put newRawData to the back of nodes
		
	}
	build();
}


/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/

void huffman(const std::string &fileName)
{
	Huffman huffmanTree;

	//open the file
	ifstream fin(fileName.c_str());

	if (fin.fail())
		cout << "Error: could not read file.\n";
	//if the file is open
	if (fin.is_open())
	{
		std::list<std::string> sequence; //create a sequence list
		std::string ID; //create a ID string
		
		// while there are words to pull from the file, pull them
		while (fin >> ID)
		{
			float huffFrequency; //declade de huffman frequency
			fin >> huffFrequency; // get the frequence from the file

			//create a pair with frequency and ID
			huffmanPair data(huffFrequency, ID);
			//add pair to huffmanTree
			huffmanTree.addElements(data);
			//store ID to hold the sequence
			sequence.push_back(ID);
		}
		//close the file
		fin.close();

		huffmanTree.build(); //call the function build

		PairStringList codes; //codes of the string
		getHuffmanCode(huffmanTree.nodes.front(), "", codes);//called the function to get the codes
		PairStringList result; // the string result

		// go through the sequence of words
		for (std::list<std::string>::iterator sit = sequence.begin(); sit!= sequence.end(); ++sit)
		{
			std::string code; //create a code string
			for(PairStringList::iterator it = codes.begin(); it != codes.end();++it)
			{
				if((*it).getFirst()==*sit) // if the pair string is equal to the word
				{
					code = (*it).getSecond(); // get node code
					codes.erase(it); // erase code from list of strings
					break;
				}
			}
			// build a new string to be put into the results of the huffman function
			custom::pair<std::string, std::string> newData(*sit, code);
			result.push_back(newData); // puch newData to back of result
		}
		// Display the results
		for (PairStringList::iterator it = result.begin();it!= result.end();++it)
		{
			cout << (*it).getFirst() << " = " << (*it).getSecond() << endl;
		}
	
	}

	return;
}
