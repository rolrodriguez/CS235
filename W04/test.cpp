#include <iostream>
#include "deque.h"
#include <sstream>
using namespace std;

int main()
{
  string text = "!! CS235 Sam 2";
  stringstream ss(text);
  string word;

  ss >> word;
  cout << word;
}