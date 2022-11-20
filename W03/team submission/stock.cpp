/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    Jatsiri Detzani and Rolando Rodriguez
 **********************************************************************/

#include <iostream> // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>   // for STRING
#include <cassert>  // for ASSERT
#include <sstream>  // for SSTREAM
#include "stock.h"  // for STOCK_TRANSACTION
#include "queue.h"  // for QUEUE
#include <cstdlib>  // for atoi
#include <vector>   // for VECTOR
using namespace std;

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

void Stock::buy(int quantity, Dollars cost)
{
   Share shares;
   Dollars newCost(cost);
   shares.setQuantity(quantity);
   shares.setValue(Dollars(cost));
   portfolio.push(shares);
   return;
}

void Stock::sell(int quantity, Dollars price)
{
   SellTransaction transaction(&portfolio, &history, quantity, price);
   proceeds += transaction.getProfit();
   //history.push(transaction);
}

void Stock::display() const
{
   custom::queue<Share> tempPortfolio = portfolio;
   custom::queue<SellTransaction> tempHistory = history;

   if (!tempPortfolio.empty())
   {
      cout << "Currently held:";
      while (!tempPortfolio.empty())
      {
         Share singleShare = tempPortfolio.front();
         tempPortfolio.pop();
         cout << "\n\tBought " << singleShare.getQuantity()
              << " shares at " << singleShare.getValue();
      }
      cout << endl;
   }

   SellTransaction singleRecord;
   if (!tempHistory.empty())
   {
      cout << "Sell History:";
      while (!tempHistory.empty())
      {
         singleRecord = tempHistory.front();
         tempHistory.pop();
         cout << "\n\tSold " << singleRecord.getSharesQuantity()
              << " shares at " << singleRecord.getValue()
              << " for a profit of " << singleRecord.getProfit();
      }
      cout << endl;
   }
   cout << "Proceeds: " << getProceeds() << endl;
}

Stock::SellTransaction::SellTransaction(custom::queue<Share> *shares, custom::queue<SellTransaction> *history, int quantitySold, Dollars price)
{
   int numShares;
   sharesQuantity = 0;
   Dollars benefit = 0;
   Dollars total = 0;
   Share shareToSell;
   SellTransaction sale;
   if (!shares->empty())
   {
      while (quantitySold > 0)
      {
         shareToSell = shares->front();
         if (quantitySold >= shareToSell.getQuantity())
         {
            numShares = shareToSell.getQuantity();
         }
         else
         {
            numShares = quantitySold;
         }
         quantitySold -= numShares;
         shares->front().setQuantity(shareToSell.getQuantity() - numShares);
         sharesQuantity += numShares;
         benefit = (price - shares->front().getValue()) * numShares;
         total += benefit;
         if (shares->front().getQuantity() == 0)
         {
            shares->pop();
         }
         value = price;
         profit = total;
         sale.setProfit(benefit);
         sale.setSharesQuantity(numShares);
         sale.setValue(price);
         history->push(sale);
      }
   }
}

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   std::string instruction;
   Stock stock;
   string operation;
   Dollars shareUnitPrice;
   cin.clear();
   cin.ignore();
   do
   {

      cout << "> ";
      getline(cin, instruction);
      std::vector<string> tokenVector = tokenizeBySpaces(instruction);
      std::stringstream ss(tokenVector[2]);
      ss >> shareUnitPrice;
      operation = tokenVector[0];

      if (operation == "buy")
      {
         stock.buy(atoi(tokenVector[1].c_str()), shareUnitPrice);
      }
      else if (operation == "sell")
      {
         stock.sell(atoi(tokenVector[1].c_str()), shareUnitPrice);
      }
      else if (operation == "display")
      {
         stock.display();
      }

   } while (operation != "quit");
}
