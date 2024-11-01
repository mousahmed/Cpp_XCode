#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include <optional>
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

/**
 * Tokenises a given CSV line into a vector of strings based on the specified separator.
 *
 * @param csvLine The string containing the CSV line to be tokenised.
 * @param separator The character used to separate tokens in the CSV line.
 * @return A vector of strings containing the tokens.
 */
vector<string> tokenise(const string &csvLine, char separator)
{
  vector<string> tokens;
  string token;
  for (const char &c : csvLine)
  {
    if (c == separator)
    {
      if (!token.empty())
      {
        tokens.push_back(token);
        token.clear();
      }
    }
    else
    {
      token += c;
    }
  }
  if (!token.empty())
  {
    tokens.push_back(token);
  }
  return tokens;
}

/**
 * @brief Creates an OrderBookEntry from a vector of strings.
 *
 * This function takes a vector of strings as input and attempts to create an OrderBookEntry object.
 * The vector must contain exactly 5 elements: timestamp, product, order type (either "bid" or "ask"),
 * price, and amount. If the vector does not contain exactly 5 elements, or if there is an error
 * converting the price or amount to a double, the function will return an empty optional.
 *
 * @param tokens A vector of strings containing the necessary data to create an OrderBookEntry.
 * @return An optional OrderBookEntry. If the input is invalid or an error occurs, returns nullopt.
 */
optional<OrderBookEntry> createOrderBookEntry(const vector<string> &tokens)
{
  if (tokens.size() != 5)
  {
    cerr << "Invalid number of tokens: " << tokens.size() << endl;
    return nullopt;
  }

  try
  {
    string timestamp = tokens[0];
    string product = tokens[1];
    OrderBookType orderType = tokens[2] == "bid" ? OrderBookType::bid : OrderBookType::ask;
    double price = stod(tokens[3]);
    double amount = stod(tokens[4]);
    return OrderBookEntry(price, amount, timestamp, product, orderType);
  }
  catch (const exception &e)
  {
    cerr << "Error creating OrderBookEntry: " << e.what() << endl;
    return nullopt;
  }
}

int main()
{
  // MerkelMain app{};
  // app.init();
  // vector<OrderBookEntry> orders = app.getOrders();
  // Calculating and displaying results
  // cout << "Average Price: " << computeAveragePrice(orders) << endl;
  // cout << "Lowest Price: " << computeLowPrice(orders) << endl;
  // cout << "Highest Price: " << computeHighPrice(orders) << endl;
  // cout << "Price Spread: " << computePriceSpread(orders) << endl;

  string csvFileName = "20200317.csv";
  ifstream file(csvFileName);
  if (!file.is_open())
  {
    cerr << "Could not open the file - '" << csvFileName << "'" << endl;
    return 1;
  }
  vector<OrderBookEntry> orders;
  while (file.good())
  {
    string line;
    getline(file, line);
    cout << line << endl;
    vector<string> tokens = tokenise(line, ',');
    auto entryOpt = createOrderBookEntry(tokens);
    if (entryOpt.has_value())
    {
      orders.push_back(entryOpt.value());
    }
  }
  file.close();

  cout << "Average Price: " << computeAveragePrice(orders) << endl;
  cout << "Lowest Price: " << computeLowPrice(orders) << endl;
  cout << "Highest Price: " << computeHighPrice(orders) << endl;
  cout << "Price Spread: " << computePriceSpread(orders) << endl;

  return 0;
}