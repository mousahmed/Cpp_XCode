#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class OrderBookType
{
  bid,
  ask
};

class OrderBookEntry
{
public:
  double price;
  double amount;
  string timestamp;
  string product;
  OrderBookType orderType;

  OrderBookEntry(double price, double amount, string timestamp, string product, OrderBookType orderType)
  {
    this->price = price;
    this->amount = amount;
    this->timestamp = timestamp;
    this->product = product;
    this->orderType = orderType;
  }
};

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
void printOptions()
{
  cout << "1: Print help" << endl;
  cout << "2: Print exchange stats" << endl;
  cout << "3: Place an ask" << endl;
  cout << "4: Place a bid" << endl;
  cout << "5: Print Wallet" << endl;
  cout << "6: Continue" << endl;
  cout << "===============================" << endl;
}

int getUserOption()
{
  int userOption;
  cout << "Type in 1-6" << endl;
  cin >> userOption;
  return userOption;
}

void printHelp()
{
  cout << "Help- choose options from the menu" << endl;
  cout << "and follow the on screen instructions." << endl;
}

void printExchangeStats()
{
  cout << "Market looks good" << endl;
}

void placeAsk()
{
  cout << "Make an offer - enter the amount" << endl;
}

void placeBid()
{
  cout << "Make a bid - enter the amount" << endl;
}

void printWallet()
{
  cout << "Your wallet is empty" << endl;
}

void continueToNextTimeFrame()
{
  cout << "Going to next time frame" << endl;
}

void proccessUserOption(int userOption)
{
  switch (userOption)
  {
  case 1:
    printHelp();
    break;
  case 2:
    printExchangeStats();
    break;
  case 3:
    placeAsk();
    break;
  case 4:
    placeBid();
    break;
  case 5:
    printWallet();
    break;
  case 6:
    continueToNextTimeFrame();
    break;
  default:
    cout << "Invalid input" << endl;
  }
}

int main()
{
  // int userOption;
  // while (true)
  // {
  //   printOptions();
  //   userOption = getUserOption();
  //   proccessUserOption(userOption);
  // }

  // Creating multiple OrderBookEntry objects and adding them to a vector
  vector<OrderBookEntry> orders;
  orders.push_back(OrderBookEntry(10000, 0.002, "2021/01/01 10:00:00", "BTC/USDT", OrderBookType::bid));
  orders.push_back(OrderBookEntry(10100, 0.004, "2021/01/01 10:01:00", "BTC/USDT", OrderBookType::ask));
  orders.push_back(OrderBookEntry(9900, 0.003, "2021/01/01 10:02:00", "BTC/USDT", OrderBookType::bid));
  orders.push_back(OrderBookEntry(10200, 0.001, "2021/01/01 10:03:00", "BTC/USDT", OrderBookType::ask));

  // Calculating and displaying results
  cout << "Average Price: " << computeAveragePrice(orders) << endl;
  cout << "Lowest Price: " << computeLowPrice(orders) << endl;
  cout << "Highest Price: " << computeHighPrice(orders) << endl;
  cout << "Price Spread: " << computePriceSpread(orders) << endl;

  return 0;
}