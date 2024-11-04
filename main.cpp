#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
using namespace std;

/**
 * Computes the average price of all OrderBookEntry objects in the given vector.
 *
 * @param entries A vector of OrderBookEntry objects.
 * @return The average price as a double. Returns 0.0 if the vector is empty.
 */
double computeAveragePrice(vector<OrderBookEntry> &entries)
{
  if (entries.empty())
    return 0.0;

  double total = 0.0;
  for (const OrderBookEntry &entry : entries)
  {
    total += entry.price;
  }
  return total / entries.size();
}

/**
 * Finds the lowest price among all OrderBookEntry objects in the given vector.
 *
 * @param entries A vector of OrderBookEntry objects.
 * @return The lowest price as a double. Returns 0.0 if the vector is empty.
 */
double computeLowPrice(vector<OrderBookEntry> &entries)
{
  if (entries.empty())
    return 0.0;

  double lowPrice = entries[0].price;
  for (const OrderBookEntry &entry : entries)
  {
    if (entry.price < lowPrice)
    {
      lowPrice = entry.price;
    }
  }
  return lowPrice;
}

/**
 * Finds the highest price among all OrderBookEntry objects in the given vector.
 *
 * @param entries A vector of OrderBookEntry objects.
 * @return The highest price as a double. Returns 0.0 if the vector is empty.
 */
double computeHighPrice(vector<OrderBookEntry> &entries)
{
  if (entries.empty())
    return 0.0;

  double highPrice = entries[0].price;
  for (const OrderBookEntry &entry : entries)
  {
    if (entry.price > highPrice)
    {
      highPrice = entry.price;
    }
  }
  return highPrice;
}

/**
 * Computes the price spread, which is the difference between the highest and lowest prices
 * in the given vector of OrderBookEntry objects.
 *
 * @param entries A vector of OrderBookEntry objects.
 * @return The price spread as a double. Returns 0.0 if the vector is empty.
 */
double computePriceSpread(vector<OrderBookEntry> &entries)
{
  if (entries.empty())
    return 0.0;

  double lowPrice = computeLowPrice(entries);
  double highPrice = computeHighPrice(entries);
  return highPrice - lowPrice;
}

int main()
{
  MerkelMain app{};
  app.init();
  vector<OrderBookEntry> orders = app.getOrders();
  // Calculating and displaying results
  cout << "Average Price: " << computeAveragePrice(orders) << endl;
  cout << "Lowest Price: " << computeLowPrice(orders) << endl;
  cout << "Highest Price: " << computeHighPrice(orders) << endl;
  cout << "Price Spread: " << computePriceSpread(orders) << endl;

  return 0;
}