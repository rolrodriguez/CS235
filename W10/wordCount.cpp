/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    Rolando & Jatsiri
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype
#include <string>
#include <fstream>      
#include <iostream>     
using namespace std;
using namespace custom;

/***************************************************
 * readFile()
 * Read the file and store the content of the file in a map
 **************************************************/
void readFile(map <string, int> & counts, const string & fileName)
{
	string words; //string to store the word of the file

	ifstream fin;
	fin.open(fileName);// open the file

    //if the file is unable to open, display an error
	if (fin.fail())
	{
		cout << "Unable to open the file" << endl; 
		return;
	}

	//while the file is not end, store the words in the map 
	while (fin >> words)
	{
		counts[words]++;                
										
	}
}


/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
	map <string, int> counts; //create a map
	string fileName; //string for input filename
 
	//ask for filename
	cout << "What is the filename to be counted? ";
	cin >> fileName;

	// pass file and the map created to store the words in the file
	readFile(counts, fileName); 

	string userInput; //string for user input

	//as for a word to be found
	cout << "What word whose frequency is to be found. Type ! when done" << endl;
	cout << "> ";
	cin >> userInput;

    //while the user input is different of '!', display the word and the frequency of the word in the file and ask for other word
	while (userInput != "!") 
	{
		cout << "\t" << userInput << " : " << counts[userInput] << endl;
		cout << "> ";
		cin >> userInput;
	}

}
