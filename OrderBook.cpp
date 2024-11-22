#include "OrderBook.h"
#include <unordered_set>
#include <algorithm>

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

std::string OrderBook::getEarliestTime()
{
  if (orders.empty())
    return "";
  return orders.front().timestamp;
}

std::string OrderBook::getNextTime(const std::string &timestamp)
{
  for (const auto &order : orders)
  {
    if (order.timestamp > timestamp)
    {
      return order.timestamp;
    }
  }
  return OrderBook::getEarliestTime();
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

void OrderBook::insertOrder(OrderBookEntry &order)
{
  orders.push_back(order);
  std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}