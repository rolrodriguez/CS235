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
#include "queue.h"    // for QUEUE
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
   // String stream to make it easier to manipulate strings
   std::stringstream ss(text);
   std::string results;
   // Vector to store the tokens
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
 * BUY
 *
 * Pushes new stocks to the portfolio for later sale.
 *****************************************************/
void Stock::buy(int quantity, Dollars cost)
{
   Share shares;
   Dollars newCost(cost);
   shares.setQuantity(quantity);
   shares.setValue(Dollars(cost));
   portfolio.push(shares);
   return;
}

/*****************************************************
 * Sell
 * 
 * Removes elements from the portfolio for sell and
 * benefits calculation 
 *****************************************************/
void Stock::sell(int quantity, Dollars price)
{
   SellTransaction transaction(&portfolio, &history, quantity, price);
   proceeds += transaction.getProfit();
}

/*****************************************************
 * DISPLAY
 * 
 * Displays a summary to the screen showing to the 
 * purchases and sales of stock.
 *****************************************************/
void Stock::display() const
{
   // Copies the portfolio and history to print.
   custom::queue<Share> tempPortfolio = portfolio;
   custom::queue<SellTransaction> tempHistory = history;

   // This block prints the shares in the portfolio
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

   // This block prints the sales records

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
   // Prints the profit from the sales
   cout << "Proceeds: " << getProceeds() << endl;
}

/*****************************************************
 * SELL Transaction - Non default constructor
 * 
 * Creates a sell transaction where a queue of
 * shares are sold.
 *****************************************************/

Stock::SellTransaction::SellTransaction(custom::queue<Share> *shares,
                                        custom::queue<SellTransaction> *history,
                                        int quantitySold, Dollars price)
{
   // shares handled per transaction
   int numShares;
   // totalizer for shares
   sharesQuantity = 0;
   // Total benefit in Dollars.
   Dollars benefit = 0;
   Dollars total = 0;
   // Shares willing to sell
   Share shareToSell;
   SellTransaction sale;

   // Execute if there are shares in the portfolio
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
         // Reduce available from requirement
         quantitySold -= numShares;

         // Reduce from inventory
         shares->front().setQuantity(shareToSell.getQuantity() - numShares);

         // Calculate benefit for sales
         benefit = (price - shares->front().getValue()) * numShares;

         // Totalize benefits from each sale
         total += benefit;

         // If a share type is already depleted remove from queue
         if (shares->front().getQuantity() == 0)
         {
            shares->pop();
         }
         value = price;
         profit = total;

         // Save attributes from sale into a queue
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
      // get input as a whole.
      getline(cin, instruction);
      // Store tokens to capture actions
      std::vector<string> tokenVector = tokenizeBySpaces(instruction);
      std::stringstream ss(tokenVector[2]);
      ss >> shareUnitPrice;
      operation = tokenVector[0];

      // Different course of action based on the instructions
      // entered in the filed.
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
