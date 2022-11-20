#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include "stack.h"
#define VARS_NAMES "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace custom;
using std::ios;
using std::ostream;
using std::string;
using std::vector;

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

void tokenizeString2(std::string text)
{
  std::stringstream ss(text);
  std::string results;
  std::string postfix;
  stack<std::string> mystack;

  while (std::getline(ss, results, ' '))
  {
    std::cout << results << endl;
  }
}

vector<string> tokenize(string text)
{
  std::vector<std::string> myvector;
  string word = "";
  char term;
  //cout << "TEXT SIZE: " << text.length() << endl;
  for (int i = 0; i < text.length(); i++)
  {

    term = text[i];
    if (term == ' ')
    {
      continue;
    }
    else if (isOperand(term))
    {
      if (!word.empty())
      {
        myvector.push_back(word);
      }
      word = term;
    }
    else
    {
      word += term;
      if (i < text.length() - 1)
        continue;
    }
    myvector.push_back(word);
    word = "";
  }

  return myvector;
}

std::vector<std::string> tokenizeBySpaces(std::string text)
{
  std::stringstream ss(text);
  std::string results;
  std::string postfix;
  std::vector<std::string> myvector;

  while (std::getline(ss, results, ' '))
  {
    if (results == "")
      continue;
    myvector.push_back(results);
  }

  return myvector;
}

std::string convertInFixSimple(const std::string &infix)
{
  std::string postfix;
  custom::stack<char> s;
  for (int i = 0; i < infix.length(); i++)
  {

    if (isdigit(infix[i]))
    {
      postfix += infix[i];
    }
    else
    {
      while (!s.empty() && (infix[i] >= s.top()))
      {
        postfix += s.top();
        s.pop();
      }
      s.push(infix[i]);
    }
  }
  while (!s.empty())
  {

    postfix += s.top();
    s.pop();
  }

  return postfix;
}

std::string convertInFixComplex2(const std::string &infix)
{
  std::string postfix;
  custom::stack<char> stack;
  for (int i = 0; i < infix.length(); i++)
  {
    char term = infix[i];

    if (isdigit(term) || isalpha(term) || term == '.')
    {
      postfix += term;
    }
    else
    {
      switch (term)
      {
      case '(':
        stack.push(term);
        break;
      case ')':
        while (stack.top() != '(')
        {

          postfix += stack.top();
          stack.pop();
        }
        stack.pop();
        break;
      default:
        while (!stack.empty() && (term <= prec(stack.top())))
        {
          postfix += stack.top();
          stack.pop();
        }
        stack.push(term);
        break;
      }
    }
  }
  while (!stack.empty())
  {
    postfix += stack.top();
    stack.pop();
  }
  return postfix;
}

std::string convertInFixComplex(const std::string &infix)
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

template <class T>
ostream &operator<<(ostream &out, stack<T> rhs)
{
  // we need to make a copy of the stack that is backwards
  stack<T> backwards;
  while (!rhs.empty())
  {
    backwards.push(rhs.top());
    rhs.pop();
  }

  // now we will display this one
  out << "{ ";
  while (!backwards.empty())
  {
    out << backwards.top() << ' ';
    backwards.pop();
  }
  out << '}';

  return out;
}

bool isVariable(string c)
{
    if (isalpha(c[0]) || c[0] == '_')
    {
      return true;
    }
  return false;
}

string operatorToAssemblyIns(char c)
{
  string command;
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
  case '^':
    command = "EXP";
    break;
  default:
    command = "";
    break;
  }
  return command;
}

string postfixToAssembly(string postfix)
{
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
      stack.push(term);
    }
    else
    {
      rhs = stack.top();
      stack.pop();
      lhs = stack.top();
      stack.pop();
      vars = variables[varCount++];
      if (isVariable(lhs))
      {
        assembly += "\tLOD " + lhs + "\n";
      }
      else
      {
        assembly += "\tSET " + lhs + "\n";
      }
      assembly += "\t" + operatorToAssemblyIns(term[0]) + " " + rhs + "\n";
      assembly += "\tSAV ";
      assembly += vars;
      assembly += '\n';

      stack.push(vars);
    }
  }
  return assembly;
}

int main()
{

  string text = "(5.0  /  .9)*(fahrenheit - 32)";
  string postfix = convertInFixComplex(text);
  cout << "Underscore: isdigit: " << isdigit('_') << " isalpha: " << isalpha('_') << endl;
  cout << "POSTFIX:" << postfix << endl;
  cout << "ASSEMBLY: \n"
       << postfixToAssembly(postfix) << endl;

  // if (cin.fail())
  // {
  //   cin.clear();
  //   cin.ignore(256, '\n');
  // }
  // string text;

  // cout << "Enter text: ";

  // getline(cin, text);
  // vector<string> v(tokenizer(text));
  // for (int i = 0; i < v.size(); i++)
  // {
  //   cout << v[i] << endl;
  // }
}
