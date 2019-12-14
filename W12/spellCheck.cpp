/***********************************************************************
 * Module:
 *    Assignment 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Rolando Rodriguez & Jatsiri Martínez
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "spellCheck.h"
#include "list.h"
#include "hash.h"
#define MAX_SIZE 4500 // 1.5 times the max dictionary size of 3000 words

using namespace std;
/****************************************
 *  SHASH
 * A simple hash of string,
 * String will conver to ASCII table
 ****************************************/
class stringHash : public Hash <string>
{
public:
   //constructor and copy constructor
   stringHash(int numBuckets) : Hash <string>(numBuckets) {}
   stringHash(const stringHash & rhs) : Hash <string>(rhs) {}
   
   //function hash, computs and returns the index for a given element and 
   int hash(const string & value) const
   {
      int sum = 0;
      for (const char * w = value.c_str(); *w; w++)
         sum += *w;
      return sum % this->capacity();
   }
};

//converts all the words of the string to lower case, and then return the new string
string toLowerCase(string & word)
{
	string lowercase = word;
	for (string::iterator w = lowercase.begin(); w != lowercase.end();++w)
	{
		*w = tolower(*w);
	}
	return lowercase;
}

/***************************************************
 * spellChecked
 * PARAMETERS: hash of string that contains the dictionary and
 * a string that contains the input file.
 *
 * DESCRIPTION:
 * This funtion compare the words of the input file with
 * the words of the dictionary and find the misspelled words,
 * displays the misspelled words and if there is no misspelled
 * words, display a message to the user that ther is no
 * misspelled words
 *
 **************************************************/
void spellChecked(stringHash shash, const string & fileName)
{      
   //Declare variables
   string words;
   custom::list<string> errors; //create a list to save the mispelled words
   bool correct = true;
   
   //open the file
   ifstream fin;
   fin.open(fileName);

   //if there is an error to open the file, display a message
   if (fin.fail()) 
   {
      cout << "Unable to open the file.\n";
      return;
   }

   //while the string is not ended, read it
   while (fin >> words)
   {
      string word = words;
		
      //push back the word in a list if the word is incorrect 
      if (!(shash.find(toLowerCase(word))))
      {
			errors.push_back(word);
			correct = false;
      }
   }
   
   //if the words are correct, display a message to the user that there are not spelling errors
   if (correct) 
   {
      cout << "File contains no spelling errors\n";
   }
   
	//if the word is not in the dictionary or have an error, display the list of incorrect words
   else 
   {
      cout << "Misspelled: ";
      for(custom::list<string>::iterator it = errors.begin();
          it != errors.end(); ++it)
      {
         
         cout << (it == errors.begin() ? "" : ", ");
         cout << *it;
      }
		cout << endl;
   }
   
}


/***************************************************
 * dictionary()
 * PARAMETER: Hash of string.
 * DESCRIPTION:
 * Read the dictionary and insert it in the hash of strings
 *
 **************************************************/
void readDictionary(stringHash &shash)
{
   string words;
   
   //open the file
   ifstream fin;
   fin.open("/home/cs235/week12/dictionary.txt");
   
   //if there is an error to open the file, display a message
   if (fin.fail()) 
   {
      cout << "Unable to open the dictionary.\n";
      return;
   }
   
   //read the file and insert the words in the hash of strings
   while (fin >> words)
   {
      shash.insert(words);
   }
   
   fin.close();
}

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
   stringHash shash(MAX_SIZE);  //creater a hash of string   
   string file; //string for the input file
   
   //ask for the filename
   cout << "What file do you want to check? ";
   cin >> file;
   string fileName = file; 
   
   //call functions to read the dictionary 
   readDictionary(shash);
   // check the input file with the dictionary to find the errors in the words
   spellChecked(shash, fileName);
}







