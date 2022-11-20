#include <iostream>
#include "vector.h"
using namespace custom;
using std::cout;
using std::cin;

int main(){
  vector <int> v(5);
  int input;
  // do
  // {
  //   cout << "Enter value: \n";
  //   cin >> input;
  //   v.push_back(input);
  //   cout << "{ ";
  //   for (int i = 0;i < v.size(); i++){
  //     cout << v[i] << " ";
  //   }
  //   cout << "}\n";
  //   cout << "size: " << v.size() << std::endl;
  //   cout << "capacity: " << v.capacity() << std::endl;

  // } while (input);

  vector<char> v1;
  v1.push_back('a');
  v1.push_back('b');
  v1.push_back('c');
  v1.push_back('d');
  v1.push_back('e');
  vector<char>::const_iterator t1; 
  cout << "{";
  for(t1 = v1.cbegin(); t1 != v1.cend(); ++t1)
  {
    cout << *t1 << " ";
  }
  cout << "}\n";
  return 0;
}
