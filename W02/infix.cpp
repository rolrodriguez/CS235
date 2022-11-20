/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Kirby, CS 235
 * Author:
 *    Jatsiri Detzani and Rolando Rodriguez
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream> // for ISTREAM and COUT
#include <string>   // for STRING
#include <cassert>  // for ASSERT
#include <sstream>  // for SSTREAM
#include "stack.h"  // for STACK
#include <cctype>   // for ISDIGIT, ISALPHA, ISALNUM
#include <vector>   // for VECTOR
using namespace std;

// Constants for assembly code names
#define VARS_NAMES "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

/*****************************************************
 * PREC
 * Returns and integer based on the precedence 
 * of the operators: ^ * / + -
 *****************************************************/
int prec(char term)
{
   int value = 0;
   switch (term)
   {
   case '^':
      value = 3;
      break;
   case '*':
   case '/':
      value = 2;
      break;
   case '+':
   case '-':
      value = 1;
      break;
   default:
      value = -1;
      break;
   }

   return value;
}

/*****************************************************
 * IS OPERAND
 * Returns true of false if the character passed
 * is an operand of the following:
 * ( ) ^ * / + -
 *****************************************************/
bool isOperand(char c)
{
   string operands = "()^*/+-";
   for (int i = 0; i < operands.size(); i++)
   {
      if (c == operands[i])
      {
         return true;
      }
   }
   return false;
}
/*****************************************************
 * TOKENIZE STRING
 * Splits a string separated when an operand is found.
 * The result returns a vector with each token
 *****************************************************/
std::vector<std::string> tokenize(string text)
{
   std::vector<std::string> myvector;
   std::string word = "";
   char term;
   for (int i = 0; i < text.length(); i++)
   {

      term = text[i];
      // Skip the cycle if an empty space is passed
      if (term == ' ')
      {
         continue;
      }
      else if (isOperand(term))
      {
         // pass to a vector a non empty operand
         if (!word.empty())
         {
            myvector.push_back(word);
         }
         word = term;
      }
      else
      {
         // Otherwise a character or variable
         // needs to be accumulated
         word += term;
         // Do not skip pushing if this is the last
         // character
         if (i < text.length() - 1)
            continue;
      }
      myvector.push_back(word);
      word = "";
   }

   return myvector;
}
/*****************************************************
 * TOKENIZE BY SPACES
 * Splits a string separated by spaces in a vector
 * where each string is one token or word to be 
 * processed
 *****************************************************/
std::vector<std::string> tokenizeBySpaces(std::string text)
{
   std::stringstream ss(text);
   std::string results;
   std::string postfix;
   std::vector<std::string> myvector;

   // Go through all words of a line of text
   // and separate by spaces found
   while (std::getline(ss, results, ' '))
   {
      // skip if an empty string is found
      if (results == "")
         continue;
      myvector.push_back(results);
   }

   return myvector;
}

/*****************************************************
 * OPERATOR TO ASSEMBLY INS
 * Converts an arithmetic operator to its assembly
 * instruction equivalent
 *****************************************************/
std::string operatorToAssemblyIns(char c)
{
   std::string command;
   switch (c)
   {
   case '+':
      command = "ADD";
      break;
   case '-':
      command = "SUB";
      break;
   case '*':
      command = "MUL";
      break;
   case '/':
      command = "DIV";
      break;
   case '%':
      command = "MOD";
      break;
   case '^':
      command = "EXP";
      break;
   default:
      command = "";
      break;
   }
   return command;
}

/*****************************************************
 * IS VARIABLE
 * Verifies if the string provided is a variable
 * name or not.
 *****************************************************/
bool isVariable(string c)
{
   if (isalpha(c[0]) || c[0] == '_')
   {
      return true;
   }
   return false;
}

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string &infix)
{
   // Get infix split into words to process
   std::vector<std::string> words = tokenize(infix);
   std::string postfix;
   custom::stack<char> stack;
   // Go through each word of the vector
   for (int j = 0; j < words.size(); j++)
   {
      // Omit adding spaces for parentheses
      if (isalnum(words[j][0]) || (!isalnum(words[j][0]) && words[j].size() > 1))
      {
         postfix += ' ';
      }
      // Apply postfix handling to each char in a word
      for (int i = 0; i < words[j].size(); i++)
      {
         char term = words[j][i];
         // Add to the postfix: digits, variables and
         // decimal points
         if (isalnum(term) || term == '.')
         {
            postfix += term;
         }
         else
         {
            switch (term)
            {
            // Add '(' to the stack right away
            case '(':
               stack.push(term);
               break;
            // Get items from the stack until '('
            case ')':
               while (stack.top() != '(')
               {
                  postfix += ' '; // Add space
                  postfix += stack.top();
                  stack.pop();
               }
               stack.pop(); // remove '(' from stack
               break;
            default:
               // Add to postfix based on operator precedence
               while (!stack.empty() && (prec(term) <= prec(stack.top())))
               {
                  postfix += ' ';
                  postfix += stack.top();
                  stack.pop();
               }
               stack.push(term);
               break;
            }
         }
      }
   }

   while (!stack.empty())
   {
      postfix += ' ';
      postfix += stack.top();
      stack.pop();
      // Add spaces between operators
   }
   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }

      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl
              << endl;
      }
   } while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string &postfix)
{
   // Vector containing a tokenized string
   vector<string> posts = tokenizeBySpaces(postfix);
   string assembly;
   custom::stack<string> stack;
   string variables = VARS_NAMES;
   int varCount = 0;
   string vars;
   string lhs;
   string rhs;

   for (int i = 0; i < posts.size(); i++)
   {
      string term = posts[i];
      if (isalnum(term[0]) || term[0] == '.')
      {
         // push all numbers and variables
         // into the stack
         stack.push(term);
      }
      else
      {
         // once an operand is found
         // remove the variables and numbers
         // to form the assembly statements
         rhs = stack.top();
         stack.pop();
         lhs = stack.top();
         stack.pop();
         // Create new variable names to 
         // Store the results
         vars = variables[varCount++];
         // Use LOD if it's a variable, use SET otherwise
         if (isVariable(lhs))
         {
            assembly += "\tLOD " + lhs + "\n";
         }
         else
         {
            assembly += "\tSET " + lhs + "\n";
         }
         // convert the operands to the equivalent assembly commands
         assembly += "\t" + operatorToAssemblyIns(term[0]) + " " + rhs + "\n";
         assembly += "\tSAV ";
         assembly += vars;
         assembly += '\n';

         stack.push(vars);
      }
   }
   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }

      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   } while (input != "quit");
}
