#include "OrderBook.h"
#include <unordered_set>

OrderBook::OrderBook(std::string filename)
{
  orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts()
{
  std::unordered_set<std::string> productSet;
  for (const auto &order : orders)
  {
    productSet.insert(order.product);
  }
  return std::vector<std::string>(productSet.begin(), productSet.end());
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &entries)
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

double OrderBook::getHighPrice(std::vector<OrderBookEntry> &entries)
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

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
  std::vector<OrderBookEntry> result;
  for (const auto &order : orders)
  {
    if (order.orderType == type && order.product == product && order.timestamp == timestamp)
    {
      result.push_back(order);
    }
  }
  return result;
}

double OrderBook::getPriceSpread(std::vector<OrderBookEntry> &entries)
{
  if (entries.empty())
    return 0.0;

  double lowPrice = OrderBook::getLowPrice(entries);
  double highPrice = OrderBook::getHighPrice(entries);
  return highPrice - lowPrice;
}

double OrderBook::getAveragePrice(std::vector<OrderBookEntry> &entries)
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