/***********************************************************************
 * Module:
 *    PAIR
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement a pair: two values
 ************************************************************************/

#ifndef PAIR_H
#define PAIR_H

#include <iostream>  // for ISTREAM and OSTREAM

namespace custom
{

/**********************************************
 * PAIR
 * This class couples together a pair of values, which may be of
 * different types (T1 and T2). The individual values can be
 * accessed through its public members first and second.
 *
 * Additionally, when compairing two pairs, only T1 is compared. This
 * is a key in a name-value pair.
 ***********************************************/
template <class Key, class Value>
class pair
{
public:
   // constructors
   pair()                                    : first(     ), second(      ) {}
   pair(const Key & first, const Value & second) : first(first), second(second) {}
   pair(const pair <Key, Value> & rhs)   : first(rhs.first), second(rhs.second) {}

   // copy the values
   pair <Key, Value> & operator = (const pair <Key, Value> & rhs)
   {
      first  = rhs.first;
      second = rhs.second;
      return *this;
   }

   // constant fetchers
   const Key & getFirst()  const { return first;  }
   const Value & getSecond() const { return second; }
   
   // compare Pairs. Only first will be compared.
   bool operator >  (const pair & rhs) const { return first >  rhs.first; }
   bool operator >= (const pair & rhs) const { return first >= rhs.first; }
   bool operator <  (const pair & rhs) const { return first <  rhs.first; }
   bool operator <= (const pair & rhs) const { return first <= rhs.first; }
   bool operator == (const pair & rhs) const { return first == rhs.first; }
   bool operator != (const pair & rhs) const { return first != rhs.first; }
   
   // these are public. We cannot validate because we know nothing about T
   Key first;
   Value second;
};

/*****************************************************
 * PAIR INSERTION
 * Display a pair for debug purposes
 ****************************************************/
template <class Key, class Value>
inline std::ostream & operator << (std::ostream & out,
                                   const pair <Key, Value> & rhs)
{
   out << '(' << rhs.first << ", " << rhs.second << ')';
   //out << rhs.second;
   return out;
}

/*****************************************************
 * PAIR EXTRACTION
 * input a pair
 ****************************************************/
template <class Key, class Value>
inline std::istream & operator >> (std::istream & in,
                                   pair <Key, Value> & rhs)
{
   in >> rhs.first >> rhs.second;
   return in;
}

}

#endif // PAIR_H
