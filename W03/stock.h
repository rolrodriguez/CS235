/***********************************************************************
 * Header:
 *    STOCK
 * Summary:
 *    This will contain just the prototype for stocksBuySell(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Jatziri Detzani and Rolando Rodriguez
 ************************************************************************/

#ifndef STOCK_H
#define STOCK_H

#include "dollars.h" // for Dollars defined in StockTransaction
#include "queue.h"    // for QUEUE
#include <vector>    // for VECTOR

#include <iostream> // for ISTREAM and OSTREAM

class Stock
{
  class Share
  {
  private:
    int quantity;
    Dollars value;

  public:
    Share() : quantity(0), value(0) {}
    Share(int newQuantity, Dollars newValue) : quantity(newQuantity), value(newValue) {}
    int getQuantity() const { return quantity; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    Dollars getValue() const { return value; }
    void setValue(Dollars newValue) { value = newValue; }
  };

  class SellTransaction
  {
  private:
    int sharesQuantity;
    Dollars value;
    Dollars profit;

  public:
    SellTransaction() : sharesQuantity(0), value(Dollars()), profit(Dollars()) {}
    SellTransaction(custom::queue<Share> *shares,
                    custom::queue<SellTransaction> *history,
                    int quantitySold, Dollars price);
    int getSharesQuantity() const { return sharesQuantity; }
    void setSharesQuantity(int quantity) { sharesQuantity = quantity; }
    Dollars getValue() const { return value; }
    void setValue(Dollars newValue) { value = newValue; }
    Dollars getProfit() const { return profit; }
    void setProfit(Dollars newProfit) { profit = newProfit; }
  };

private:
  custom::queue<Share> portfolio;
  custom::queue<SellTransaction> history;
  Dollars proceeds;

public:
  Stock() : proceeds(Dollars()){};
  void buy(int quantity, Dollars cost);
  void sell(int quantity, Dollars price);
  void display() const;
  Dollars getProceeds() const { return proceeds; }
};

// the interactive stock buy/sell function
void stocksBuySell();

// a function to separate the user input in different tokens
std::vector<std::string> tokenizeBySpaces(std::string text);

#endif // STOCK_H
