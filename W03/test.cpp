#include <iostream>
#include "queue.h"
#include "dollars.h"
#include "stock.cpp"
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;
using namespace custom;

template <class T>
ostream &operator<<(ostream &out, queue<T> q)
{
  out << "{ ";
  while (!q.empty())
  {
    out << q.front() << ' ';
    q.pop();
  }
  out << '}';
  return out;
}

void testCircular()
{

  // create
  cout << "Create a string Queue with the default constructor\n";
  queue<string> q(4);

  // instructions
  cout << "\tTo add the word \"dog\", type +dog\n";
  cout << "\tTo pop the word off the queue, type -\n";
  cout << "\tTo display the state of the queue, type *\n";
  cout << "\tTo quit, type !\n";

  // interact
  char instruction;
  string word;
  try
  {
    do
    {
      cout << "\t" << q << " > ";
      cin >> instruction;
      switch (instruction)
      {
      case '+':
        cin >> word;
        q.push(word);
        break;
      case '-':
        q.pop();
        break;
      case '*':
        cout << "Size:     " << q.size() << endl;
        cout << "Empty?    " << (q.empty() ? "Yes" : "No") << endl;
        break;
      case '!':
        break;
      default:
        cout << "Invalid command\n";
      }
    } while (instruction != '!');
  }
  catch (const char *error)
  {
    cout << error << endl;
  }

  // verify that copy works as we expect
  queue<string> qCopy(q);
  assert(q.size() == qCopy.size());
  assert(q.empty() == qCopy.empty());
  while (!q.empty())
  {
    assert(q.front() == qCopy.front());
    assert(q.back() == qCopy.back());
    assert(q.size() == qCopy.size());
    q.pop();
    qCopy.pop();
  }
}

int main()
{
  //testCircular();

  // queue<int> q1;
  // int iters = 30;
  // for (int i = 0; i < iters; i++)
  // {
  //   q1.push(i);
  // }

  // for (int i = 0; i < iters; i++)
  // {
  //   q1.pop();
  // }

  // for (int i = 0; i < iters; i++)
  // {
  //   q1.push(i);
  // }

  // queue<int> q2(q1);
  // cout << " }\n Capacity: " << q1.capacity();
  // cout << "\n Size: " << q1.size();
  // cout << " Q1:{ ";
  // while (!q1.empty())
  // {
  //   cout << q1.front() << " ";
  //   q1.pop();
  // }

  // cout << " }\n Capacity: " << q2.capacity();
  // cout << "\n Size: " << q2.size();
  // cout << " Q2:{ ";
  // while (!q2.empty())
  // {
  //   cout << q2.front() << " ";
  //   q2.pop();
  // }
}